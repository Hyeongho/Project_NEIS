// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_PlayerCharacter.h"
#include "Kwang_AnimInstance.h"
#include "../DefaultPlayerState.h"
#include "../../Projectile/KKB/Player/SwordProjectile.h"
#include "../../Effect/KKB/Player/ChargeEffect.h"
#include "../../Collider/KKB/Player/Kwang_BaseAttackCol.h"
#include "../../Collider/KKB/Player/Kwang_ThunderStormCol.h"
#include "../../Component/KKB/CoolDownComponent.h"
#include "../../GameMode/KKB/FireLandGameMode.h"
#include "../../UI/KKB/Kwang_UserWidget.h"
#include "Particles/ParticleSystemComponent.h"


AKwang_PlayerCharacter::AKwang_PlayerCharacter() :
	m_ChargeRate(0),
	m_AuraLifeTime(10.f),
	m_AuraCooldownTime(15.f),
	m_AuraActive(false),
	m_AuraSkillCount(0),
	m_AuraSkillMax(5),
	m_DashCooldownTime(5.f),
	m_DashDistance(5000.f)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangSunrise.KwangSunrise'"));

	if (MeshAsset.Succeeded()) 
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/KKB/Player/Anim/AB_Kwang.AB_Kwang_C'"));

	if (AnimClass.Succeeded()) 
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);


	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetCapsuleComponent()->SetCollisionProfileName("Player");

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Camera Setting
	m_SpringArm->TargetArmLength = 1200.f;
	//m_SpringArm->TargetArmLength = 1600.f;
	m_SpringArm->SetRelativeLocation(FVector(0.0, 0.0, 170.0));
	m_SpringArm->SetRelativeRotation(FRotator(-50.0, 0.0, 0.0));

	m_SpringArm->SetupAttachment(GetCapsuleComponent());

	
	// Cooldown Comp
	// KKB 수정 필요. 매직 넘버를 전부 특정 항목에서 가져와 적용하도록 변경.
	m_DashCooldown = CreateDefaultSubobject<UCoolDownComponent>(TEXT("DashCooldown"));
	m_DashCooldown->SetCooldownTime(m_DashCooldownTime);

	m_ThunderStormCooldown = CreateDefaultSubobject<UCoolDownComponent>(TEXT("ThunderStormCooldown"));
	m_ThunderStormCooldown->SetCooldownTime(20.f);

	m_ThunderAuraCooldown = CreateDefaultSubobject<UCoolDownComponent>(TEXT("AuraCooldown"));
	m_ThunderAuraCooldown->SetCooldownTime(m_AuraCooldownTime);


	// HitEffect Setting
	m_AuraEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AuraEffectParticle"));
	m_AuraEffect->SetupAttachment(RootComponent);
	m_AuraEffect->SetAutoActivate(false);
	m_AuraEffect->SetRelativeScale3D(m_AuraEffect->GetRelativeScale3D() * 3.f);

	// Aura Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/KKB/Player/Particles/Abilities/LightStrike/FX/P_KwangBuff.P_KwangBuff'"));

	if (ParticleAsset.Succeeded())
		m_AuraEffect->SetTemplate(ParticleAsset.Object);
}

void AKwang_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 위젯 세팅
	AFireLandGameMode* GameMode = Cast<AFireLandGameMode>(GetWorld()->GetAuthGameMode());

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (IsValid(GameMode)) {
		m_PlayerWidget = GameMode->GetFirelandPlayerWidget();

		if (IsValid(m_PlayerWidget)) {

			float CurrentHP = DefaultPlayerState->GetHPMax();
			float MaxHP = DefaultPlayerState->GetHPMax();

			float Value = CurrentHP / MaxHP;

			m_PlayerWidget->SetHpRemain(Value);
			m_PlayerWidget->SetVisibility(ESlateVisibility::Visible);

			UE_LOG(LogTemp, Warning, TEXT("FireLand Player Widget Setting in Player!"));
		}
	}
}

void AKwang_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// 대쉬 사용 가능 여부 체크
	if (IsValid(m_DashCooldown)) {
		if (m_DashCooldown->IsCooldown()) {
			float Remain = m_DashCooldown->UpdateCooldown(DeltaTime);

			if (IsValid(m_PlayerWidget)) 
				m_PlayerWidget->SetSpaceRemainCoolTime(Remain);
		}
		else {
			if (IsValid(m_PlayerWidget))
				m_PlayerWidget->SetSpaceRemainCoolTime(0.f);
		}
	}

	// Skill2(썬더스톰) 사용 가능 여부 체크
	if (IsValid(m_ThunderStormCooldown)) {
		if (m_ThunderStormCooldown->IsCooldown()) {
			float Remain = m_ThunderStormCooldown->UpdateCooldown(DeltaTime);

			if (IsValid(m_PlayerWidget))
				m_PlayerWidget->SetQRemainCoolTime(Remain);
		}
		else {
			if (IsValid(m_PlayerWidget))
				m_PlayerWidget->SetQRemainCoolTime(0.f);
		}
	}

	// Skill3(오라) 사용 가능 여부 체크
	if (IsValid(m_ThunderAuraCooldown)) {
		if (m_ThunderAuraCooldown->IsCooldown()) {
			float Remain = m_ThunderAuraCooldown->UpdateCooldown(DeltaTime);

			if (IsValid(m_PlayerWidget)) {
				m_PlayerWidget->SetERemainCoolTime(Remain);
	
				if(m_AuraActive)
					m_PlayerWidget->SetESkillRemain(Remain - (m_AuraCooldownTime - m_AuraLifeTime));
			}
		}
		else {
			if (IsValid(m_PlayerWidget))
				m_PlayerWidget->SetERemainCoolTime(0.f);
		}
	}




	// 오라 액티브 도중, 플레이어의 무기를 계속해서 따라오도록 작업
	if (m_AuraActive) 
		if (IsValid(m_AuraEffect)) 
			if (m_AuraSkillCount >= m_AuraSkillMax) 
				Skill3_AuraEnd();


	// 오라 이펙트는 계속 플레이어를 따라다님.
	FVector Vec = GetMesh()->GetSocketLocation(TEXT("FX_weapon_base"));
	FRotator Rot = GetMesh()->GetSocketRotation(TEXT("FX_weapon_base"));

	m_AuraEffect->SetWorldLocation(Vec);
	m_AuraEffect->SetWorldRotation(Rot);

}

float AKwang_PlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (IsValid(DefaultPlayerState)) {
		if (DefaultPlayerState->AddHP(-1 * DamageAmount)) {
			// Dead

			//return DamageAmount;
		}

		float CurrentHP = DefaultPlayerState->GetHP();
		float MaxHP = DefaultPlayerState->GetHPMax();
		float Value = CurrentHP / MaxHP;

		if(IsValid(m_PlayerWidget))
			m_PlayerWidget->SetHpRemain(Value);
	}


	return DamageAmount;
}

void AKwang_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKwang_PlayerCharacter::AddSkill1Charge()
{
	// Energy ball 스킬의 차지 단계를 증감
	m_ChargeRate++;
}

void AKwang_PlayerCharacter::Attack()
{
	FVector FwdVec = GetMesh()->GetForwardVector();

	float temp = FwdVec.X;
	FwdVec.X = FwdVec.Y * -1.f;
	FwdVec.Y = temp * 1.f;

	FwdVec = GetTransform().GetLocation() + FwdVec * 100.f;

	FRotator CharRot = FRotator(0.0, GetMesh()->GetRelativeRotation().Yaw, 0.0);

	// 공격 범위에 충돌체를 생성하여, 피해를 준다.
	GetWorld()->SpawnActor<AKwang_BaseAttackCol>(FwdVec, CharRot);
}

void AKwang_PlayerCharacter::Attack_Enhance()
{
	// 오라가 켜져있다면 추가 효과 발동.
	if (m_AuraActive) {
		FVector FwdVec = GetMesh()->GetForwardVector();

		float temp = FwdVec.X;
		FwdVec.X = FwdVec.Y * -1.f;
		FwdVec.Y = temp * 1.f;

		FwdVec = GetTransform().GetLocation() + FwdVec * 100.f;

		FRotator CharRot = FRotator(0.0, GetMesh()->GetRelativeRotation().Yaw, 0.0);

		GetWorld()->SpawnActor<AKwang_BaseAttackCol>(FwdVec, CharRot);

		m_AuraSkillCount++;



		if (IsValid(m_PlayerWidget)) {
			int AuraSkillRemain = m_AuraSkillMax - m_AuraSkillCount;

			m_PlayerWidget->SetEBuffRemain(AuraSkillRemain);
		}

	}
}

void AKwang_PlayerCharacter::Dash()
{
	// 쿨다운이라면 사용 불가.
	if (IsValid(m_DashCooldown))
		if (m_DashCooldown->IsCooldown())
			return;


	// 대쉬 처리를 한다.
	FVector FwdVec = GetMesh()->GetForwardVector();

	float temp = FwdVec.X;
	FwdVec.X = FwdVec.Y * -1.f;
	FwdVec.Y = temp * 1.f;

	// 오라 액티브 시에는 쿨타임이 없다.
	if (m_AuraActive) {
		LaunchCharacter(FwdVec * m_DashDistance, false, false);
		m_AuraSkillCount++;


		if (IsValid(m_PlayerWidget)) {
			int AuraSkillRemain = m_AuraSkillMax - m_AuraSkillCount;

			m_PlayerWidget->SetEBuffRemain(AuraSkillRemain);
		}
	}
	else {
		LaunchCharacter(FwdVec * m_DashDistance, false, false);

		// 쿨다운 시작
		if (IsValid(m_DashCooldown))
			m_DashCooldown->StartCooldown();
	}
}

void AKwang_PlayerCharacter::Skill1_ChargeShot()
{
	// Anim Inst 실행
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill1Release();
}

void AKwang_PlayerCharacter::Skill1_ChargeShot_ActiveSkill()
{
	ShootProjectile();
}

void AKwang_PlayerCharacter::Skill2_ThunderStorm()
{
	// 쿨다운이라면 사용 불가.
	if (IsValid(m_ThunderStormCooldown))
		if (m_ThunderStormCooldown->IsCooldown())
			return;

	// Anim Inst 실행
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill2();
}

void AKwang_PlayerCharacter::Skill2_ThunderStorm_ActiveSkill()
{
	FRotator CharRot = FRotator(0.0, GetMesh()->GetRelativeRotation().Yaw, 0.0);

	// 공격 영역에 충돌체 생성하여 피해를 준다.
	 GetWorld()->SpawnActor<AKwang_ThunderStormCol>(GetActorLocation(), CharRot);

	// 쿨다운 시작
	if (IsValid(m_ThunderStormCooldown))
		m_ThunderStormCooldown->StartCooldown();
}

void AKwang_PlayerCharacter::Skill2_ThunderStorm_ActiveSkill_Enhance()
{
	// 오라가 켜져있다면 추가 효과 발동.
	if (m_AuraActive) {
		FRotator CharRot = FRotator(0.0, GetMesh()->GetRelativeRotation().Yaw, 0.0);

		GetWorld()->SpawnActor<AKwang_ThunderStormCol>(GetActorLocation(), CharRot);

		m_AuraSkillCount++;

		if (IsValid(m_PlayerWidget)) {
			int AuraSkillRemain = m_AuraSkillMax - m_AuraSkillCount;

			m_PlayerWidget->SetEBuffRemain(AuraSkillRemain);
		}
	}
}

void AKwang_PlayerCharacter::Skill3_ThunderAura()
{
	// 쿨다운이라면 사용 불가.
	if (IsValid(m_ThunderAuraCooldown))
		if (m_ThunderAuraCooldown->IsCooldown())
			return;


	// Anim Inst 실행
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill3();
}

void AKwang_PlayerCharacter::Skill3_ThunderAura_ActiveSkill()
{
	// 오라를 무기 위치와 회전에 맞추어 생성
	// 이후 LifeTime이 다 되면 오라를 삭제.
	m_AuraActive = true;

	// 오라 이펙트 활성화
	if (IsValid(m_AuraEffect))
		m_AuraEffect->Activate();

	// 일정 시간 뒤에 Aura가 자동으로 꺼지도록 세팅
	GetWorld()->GetTimerManager().ClearTimer(m_AuraLifeTimerHnd);
	GetWorld()->GetTimerManager().SetTimer(m_AuraLifeTimerHnd, this, &AKwang_PlayerCharacter::Skill3_AuraEnd, m_AuraLifeTime, false);

	// 스킬을 일정 갯수 사용하면 오라가 자동으로 꺼지게 하기 위한 변수 세팅
	m_AuraSkillCount = 0;


	// 대쉬 쿨다운 초기화
	if (IsValid(m_DashCooldown))
		m_DashCooldown->ResetCooldown();


	// 오라 위젯 활성화
	if (IsValid(m_PlayerWidget))
		m_PlayerWidget->SetEBuffRemain(m_AuraSkillMax);


	// 쿨다운 시작
	if (IsValid(m_ThunderAuraCooldown))
		m_ThunderAuraCooldown->StartCooldown();
}

void AKwang_PlayerCharacter::Skill3_AuraEnd()
{
	if (!m_AuraActive)
		return;

	// 오라를 종료하고, 오라를 삭제한다.
	m_AuraActive = false;

	if(IsValid(m_AuraEffect))
		m_AuraEffect->Deactivate();

	// 버프 초기화
	if (IsValid(m_PlayerWidget))
		m_PlayerWidget->SetEBuffRemain(0);

}

void AKwang_PlayerCharacter::ShootProjectile()
{
	FVector Vec = GetMesh()->GetSocketLocation(TEXT("FX_weapon_base"));
	FRotator Rot = GetMesh()->GetRelativeRotation();
	Rot.Yaw += 40.f;

	ASwordProjectile* ProjObj = GetWorld()->SpawnActor<ASwordProjectile>(Vec, Rot);

	if (IsValid(ProjObj)) {
		// 오라가 켜져있다면, 즉시 3단계로 발사 / 아니라면 현재 차지 단계로 발사.
		if (m_AuraActive) {
			ProjObj->Shoot(2.25);
			m_AuraSkillCount++;


			if (IsValid(m_PlayerWidget)) {
				int AuraSkillRemain = m_AuraSkillMax - m_AuraSkillCount;

				m_PlayerWidget->SetEBuffRemain(AuraSkillRemain);
			}
		}
		else 
			ProjObj->Shoot((float)pow(1.5, m_ChargeRate));

		m_ChargeRate = 0;
	}
}

void AKwang_PlayerCharacter::HidePlayerWidget()
{
	if (IsValid(m_PlayerWidget))
		m_PlayerWidget->HiddenAll();
}

void AKwang_PlayerCharacter::VisiblePlayerWidget()
{
	if (IsValid(m_PlayerWidget))
		m_PlayerWidget->VisibleAll();
}
