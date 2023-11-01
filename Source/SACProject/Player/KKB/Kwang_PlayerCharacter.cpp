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
	// KKB ���� �ʿ�. ���� �ѹ��� ���� Ư�� �׸񿡼� ������ �����ϵ��� ����.
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

	// �÷��̾� ���� ����
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


	// �뽬 ��� ���� ���� üũ
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

	// Skill2(�������) ��� ���� ���� üũ
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

	// Skill3(����) ��� ���� ���� üũ
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




	// ���� ��Ƽ�� ����, �÷��̾��� ���⸦ ����ؼ� ��������� �۾�
	if (m_AuraActive) 
		if (IsValid(m_AuraEffect)) 
			if (m_AuraSkillCount >= m_AuraSkillMax) 
				Skill3_AuraEnd();


	// ���� ����Ʈ�� ��� �÷��̾ ����ٴ�.
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
	// Energy ball ��ų�� ���� �ܰ踦 ����
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

	// ���� ������ �浹ü�� �����Ͽ�, ���ظ� �ش�.
	GetWorld()->SpawnActor<AKwang_BaseAttackCol>(FwdVec, CharRot);
}

void AKwang_PlayerCharacter::Attack_Enhance()
{
	// ���� �����ִٸ� �߰� ȿ�� �ߵ�.
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
	// ��ٿ��̶�� ��� �Ұ�.
	if (IsValid(m_DashCooldown))
		if (m_DashCooldown->IsCooldown())
			return;


	// �뽬 ó���� �Ѵ�.
	FVector FwdVec = GetMesh()->GetForwardVector();

	float temp = FwdVec.X;
	FwdVec.X = FwdVec.Y * -1.f;
	FwdVec.Y = temp * 1.f;

	// ���� ��Ƽ�� �ÿ��� ��Ÿ���� ����.
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

		// ��ٿ� ����
		if (IsValid(m_DashCooldown))
			m_DashCooldown->StartCooldown();
	}
}

void AKwang_PlayerCharacter::Skill1_ChargeShot()
{
	// Anim Inst ����
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
	// ��ٿ��̶�� ��� �Ұ�.
	if (IsValid(m_ThunderStormCooldown))
		if (m_ThunderStormCooldown->IsCooldown())
			return;

	// Anim Inst ����
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill2();
}

void AKwang_PlayerCharacter::Skill2_ThunderStorm_ActiveSkill()
{
	FRotator CharRot = FRotator(0.0, GetMesh()->GetRelativeRotation().Yaw, 0.0);

	// ���� ������ �浹ü �����Ͽ� ���ظ� �ش�.
	 GetWorld()->SpawnActor<AKwang_ThunderStormCol>(GetActorLocation(), CharRot);

	// ��ٿ� ����
	if (IsValid(m_ThunderStormCooldown))
		m_ThunderStormCooldown->StartCooldown();
}

void AKwang_PlayerCharacter::Skill2_ThunderStorm_ActiveSkill_Enhance()
{
	// ���� �����ִٸ� �߰� ȿ�� �ߵ�.
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
	// ��ٿ��̶�� ��� �Ұ�.
	if (IsValid(m_ThunderAuraCooldown))
		if (m_ThunderAuraCooldown->IsCooldown())
			return;


	// Anim Inst ����
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill3();
}

void AKwang_PlayerCharacter::Skill3_ThunderAura_ActiveSkill()
{
	// ���� ���� ��ġ�� ȸ���� ���߾� ����
	// ���� LifeTime�� �� �Ǹ� ���� ����.
	m_AuraActive = true;

	// ���� ����Ʈ Ȱ��ȭ
	if (IsValid(m_AuraEffect))
		m_AuraEffect->Activate();

	// ���� �ð� �ڿ� Aura�� �ڵ����� �������� ����
	GetWorld()->GetTimerManager().ClearTimer(m_AuraLifeTimerHnd);
	GetWorld()->GetTimerManager().SetTimer(m_AuraLifeTimerHnd, this, &AKwang_PlayerCharacter::Skill3_AuraEnd, m_AuraLifeTime, false);

	// ��ų�� ���� ���� ����ϸ� ���� �ڵ����� ������ �ϱ� ���� ���� ����
	m_AuraSkillCount = 0;


	// �뽬 ��ٿ� �ʱ�ȭ
	if (IsValid(m_DashCooldown))
		m_DashCooldown->ResetCooldown();


	// ���� ���� Ȱ��ȭ
	if (IsValid(m_PlayerWidget))
		m_PlayerWidget->SetEBuffRemain(m_AuraSkillMax);


	// ��ٿ� ����
	if (IsValid(m_ThunderAuraCooldown))
		m_ThunderAuraCooldown->StartCooldown();
}

void AKwang_PlayerCharacter::Skill3_AuraEnd()
{
	if (!m_AuraActive)
		return;

	// ���� �����ϰ�, ���� �����Ѵ�.
	m_AuraActive = false;

	if(IsValid(m_AuraEffect))
		m_AuraEffect->Deactivate();

	// ���� �ʱ�ȭ
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
		// ���� �����ִٸ�, ��� 3�ܰ�� �߻� / �ƴ϶�� ���� ���� �ܰ�� �߻�.
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
