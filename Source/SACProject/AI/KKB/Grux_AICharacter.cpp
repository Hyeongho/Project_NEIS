// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_AICharacter.h"
#include "Grux_AIAnimInst.h"
#include "Grux_AIController.h"
#include "Object/Grux_EarthquakeBox.h"
#include "../AIState.h"
#include "../../Collider/KKB/AI/Grux_BaseAttackCol.h"
#include "../../Collider/KKB/AI/Grux_DoublePainCol.h"
#include "../../Collider/KKB/AI/Grux_StampedeAttackCol.h"
#include "../../Component/KKB/CoolDownComponent.h"
#include "../../UI/CJH/DamageTextWidget.h"
#include "../../UI/KKB/FireLandWidget.h"
#include "../../GameMode/KKB/FireLandGameMode.h"

AGrux_AICharacter::AGrux_AICharacter() :
	m_StampedeCoolTime(10.f),
	m_StampedeDamage(100),
	m_StampedeStunTime(3.f),
	m_IsStun(false),
	m_EarthquakeCoolTime(1000.f),
	m_EarthquakeDamage(50),
	m_TraceStampedeTarget(false),
	m_IsRun(false),
	m_TraceMaxTime(4.f),
	m_TraceCurTime(0.f),
	m_RunSpeed(40000.f),
	m_StunCurTime(0.f),
	m_IsBerserk(false)
{
	PrimaryActorTick.bCanEverTick = true;

	// 캡슐 컴포넌트 설정
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetCapsuleComponent()->SetCollisionProfileName("AI");


	// 메쉬 설정
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 메쉬 애셋 적용
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Skins/Tier_2/Grux_Beetle_Molten/Meshes/GruxMolten.GruxMolten'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);


	// 스킬 쿨타임 컴포넌트
	m_StampedeCooldown = CreateDefaultSubobject<UCoolDownComponent>("StampedeCooldownComponent");
	m_EarthquakeCooldown = CreateDefaultSubobject<UCoolDownComponent>("EarthquakeCooldownComponent");

	// 애니메이션 블루프린트 적용
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/KKB/AI/Grux/Anim/AB_Grux.AB_Grux_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);


	// AI Controller 적용
	AIControllerClass = AGrux_AIController::StaticClass();


	// 위젯 클래스 세팅
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/CJH/Blueprints/Widget/W_DamageText.W_DamageText_C'"));

	if(WidgetClass.Succeeded())
		m_DamageTextWidgetClass = WidgetClass.Class;



	// 기타 변수 선언
	FAIDataTable* Data = new FAIDataTable;
	Data->HP = 400;
	Data->AttackPoint = 30;
	Data->MoveSpeed = 300.f;
	Data->AttackDistance = 400.f;
	Data->InteractionDistance = 2000.f;

	m_AIState->SetInfo("GruxMonster", Data);
}

void AGrux_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	// 몬스터 스케일을 키우기.
	SetActorRelativeScale3D(GetActorRelativeScale3D() * 2.f);

	// 스킬 쿨타임 세팅
	// BP에 적용한 내용을 이곳에서도 적용할 수 있도록 BeginPlay에서 작업.
	m_StampedeCooldown->SetCooldownTime(m_StampedeCoolTime);
	m_EarthquakeCooldown->SetCooldownTime(m_EarthquakeCoolTime);


	UE_LOG(LogTemp, Warning, TEXT("FireLand Grux Begin Play!"));


	// 보스 위젯 세팅
	AFireLandGameMode* GameMode = Cast<AFireLandGameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode)) {
		m_FireLandWidget = GameMode->GetFirelandBossWidget();

		if (IsValid(m_FireLandWidget)) {
			m_FireLandWidget->SetCurHP(m_AIState->GetHPMax());
			m_FireLandWidget->SetMaxHP(m_AIState->GetHPMax());

			m_FireLandWidget->SetVisibility(ESlateVisibility::Visible);


			UE_LOG(LogTemp, Warning, TEXT("FireLand BossWidget Setting!"));
		}
	}
}

bool AGrux_AICharacter::IsStampedeActive() const
{
	bool Cooltime = false;

	if (IsValid(m_StampedeCooldown))
		Cooltime = !m_StampedeCooldown->IsCooldown();

	return Cooltime;
}

bool AGrux_AICharacter::IsEarthquakeActive() const
{
	bool Cooltime = false;

	if (IsValid(m_EarthquakeCooldown))
		Cooltime = !m_EarthquakeCooldown->IsCooldown();

	return Cooltime;
}

bool AGrux_AICharacter::IsDead() const
{
	return m_AIState->GetHP() <= 0;
}

void AGrux_AICharacter::SetStun()
{
	if (!m_IsRun)
		return;

	m_IsRun = false;

	Skill2_Stampede_Stun();
}

void AGrux_AICharacter::StartStampedeCooldown()
{
	if (IsValid(m_StampedeCooldown))
		m_StampedeCooldown->StartCooldown();
}

void AGrux_AICharacter::SetStampedeTarget(const FVector& TargetPoint)
{
	m_StampedeTargetPoint = TargetPoint;
}

void AGrux_AICharacter::Attack()
{
	if (m_IsRun)
		return;

	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim)) 
		Anim->Attack_Anim();
}

void AGrux_AICharacter::Attack_Active()
{
	// 충돌체를 생성해 데미지를 준다.
	GetWorld()->SpawnActor<AGrux_BaseAttackCol>(GetActorLocation() + GetActorForwardVector() * 300.f, FRotator(0.0, GetActorRotation().Yaw, 0.0));
}

void AGrux_AICharacter::Skill1_DoublePain()
{
	// Anim Inst 실행
	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim)) 
		Anim->Skill1_DoublePain_Anim();
}

void AGrux_AICharacter::Skill1_DoublePain_ActiveSkill()
{
	// 충돌체를 생성해 데미지를 준다.
	GetWorld()->SpawnActor<AGrux_DoublePainCol>(GetActorLocation() + GetActorForwardVector() * 300.f, FRotator(0.0, GetActorRotation().Yaw, 0.0));
}

void AGrux_AICharacter::Skill2_Stampede_Ready()
{
	// Anim Inst 실행
	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim)) 
		Anim->Skill2_StampedeReady_Anim();
}

void AGrux_AICharacter::Skill2_Stampede_Run()
{
	// Anim Inst 실행
	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill2_StampedeRun_Anim();

	m_IsRun = true;
}

void AGrux_AICharacter::Skill2_Stampede_Attack()
{
	// Anim Inst 실행
	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill2_StampedeAttack_Anim();
}

void AGrux_AICharacter::Skill2_Stampede_Attack_ActiveSkill()
{
	// 주위에 충돌체를 생성하며 충돌한 대상에게 피해를 주고 밀쳐낸다.
	GetWorld()->SpawnActor<AGrux_StampedeAttackCol>(GetActorLocation() + GetActorForwardVector() * 300.f, FRotator(0.0, GetActorRotation().Yaw, 0.0));
}

void AGrux_AICharacter::Skill2_Stampede_Stun()	
{
	m_IsStun = true;

	Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance())->SetStun();
}

void AGrux_AICharacter::Skill3_Earthquake()
{
	// Anim Inst 실행
	UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim)) 
		Anim->Skill3_Earthquake_Anim();
}

void AGrux_AICharacter::Skill3_Earthquake_ActiveSkill()
{
	// 어스퀘이크 실행.
	m_EarthquakeBox = GetWorld()->SpawnActor<AGrux_EarthquakeBox>();

	// 쿨다운 시작
	m_EarthquakeCooldown->StartCooldown();
}

void AGrux_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead()) {
		UGrux_AIAnimInst* Anim = Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance());

		if (IsValid(Anim))
			Anim->SetDeath();

		return;
	}



	// Skill Cooldown Update
	if (IsValid(m_StampedeCooldown))
		if (m_StampedeCooldown->IsCooldown())
			m_StampedeCooldown->UpdateCooldown(DeltaTime);

	if (IsValid(m_EarthquakeCooldown))
		if (m_EarthquakeCooldown->IsCooldown())
			m_EarthquakeCooldown->UpdateCooldown(DeltaTime);

	if (m_TraceStampedeTarget) {
		// 타겟 추적 중
		m_TraceCurTime += DeltaTime;

		m_StampedeTargetPoint = Cast<AGrux_AIController>(GetController())->GetTargetPosByBB();

		// 대기 시간 종료 시, 런
		if (m_TraceCurTime >= m_TraceMaxTime) {
			m_TraceStampedeTarget = false;
			m_IsRun = true;

			Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance())->Skill2_StampedeRun_Anim();

			m_TraceCurTime = 0.f;
		}

		FVector MyPoint = GetActorLocation();
		MyPoint.Z = m_StampedeTargetPoint.Z;

		FVector Dir = (m_StampedeTargetPoint - MyPoint).GetSafeNormal();
		SetActorRotation(Dir.Rotation());
	}


	if (m_IsRun) {
		// Ready에서 설정된 타겟 지점을 향해 달리기
		float Distance = FVector::Dist(m_StampedeTargetPoint, GetActorLocation());

		if (Distance < 400.f) {
			m_IsRun = false;
			Skill2_Stampede_Attack();
		}
		else {
			FVector Dir = (m_StampedeTargetPoint - GetActorLocation()).GetSafeNormal();

			GetCharacterMovement()->Velocity += Dir * DeltaTime * m_RunSpeed;
		}
	}


	if (m_IsStun) {
		m_StunCurTime += DeltaTime;

		if (m_StunCurTime >= m_StampedeStunTime) {
			m_IsStun = false;

			Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance())->SetStunRelease();

			m_StunCurTime = 0.f;
		}
	}
}

float AGrux_AICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Damage Widget
	if (IsValid(m_DamageTextWidgetClass))
	{
		UDamageTextWidget* DamageWidget = CreateWidget<UDamageTextWidget>(GetWorld(), m_DamageTextWidgetClass);

		if (IsValid(DamageWidget))
		{
			DamageWidget->AddToViewport();

			DamageWidget->SetDamageText(DamageAmount * 10, GetActorLocation());

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			FVector2D ScreenPosition;
			PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
			DamageWidget->SetPositionInViewport(ScreenPosition);
		}
	}


	// Boss HPBar Widget
	if (IsValid(m_FireLandWidget)) 
		m_FireLandWidget->SetCurHP(m_AIState->GetHP());


	// 피해 처리
	if (m_AIState->Damage(DamageAmount)) {
		// 죽었음.
		Cast<UGrux_AIAnimInst>(GetMesh()->GetAnimInstance())->SetDeath();
		
		if (IsValid(m_EarthquakeBox))
			m_EarthquakeBox->Destroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		// HPBar Widget 삭제
		if (IsValid(m_FireLandWidget))
			m_FireLandWidget->RemoveFromParent();



		return DamageAmount;
	}


	// HP가 절반 이하일때.
	if (m_AIState->IsHalfHP()) {
		if (!m_IsBerserk) {
			m_IsBerserk = true;

			m_RunSpeed *= 2.f;
			m_TraceMaxTime /= 2.f;


			AFireLandGameMode* GameMode = Cast<AFireLandGameMode>(GetWorld()->GetAuthGameMode());

			if (IsValid(GameMode)) {
				GameMode->Audio_Phase1Stop();
				GameMode->Audio_Phase2Start();
			}
		}
	}

	return DamageAmount;
}
