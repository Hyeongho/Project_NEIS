// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_AnimInstance.h"
#include "Kwang_PlayerCharacter.h"
#include "Kwang_Controller.h"

UKwang_AnimInstance::UKwang_AnimInstance()
{
	m_MoveSpeed = 0.f;
	m_AttackIndex = 0;
	m_AttackEnable = true;
	m_Charging = false;
}

void UKwang_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AKwang_PlayerCharacter* Character = Cast<AKwang_PlayerCharacter>(TryGetPawnOwner());

	if (Character)
		m_Player = Character;
}

void UKwang_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (IsValid(m_Player))
	{
		UCharacterMovementComponent* Movement = m_Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			m_MoveSpeed = Movement->Velocity.Length();
		}
	}
}

void UKwang_AnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UKwang_AnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UKwang_AnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UKwang_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UKwang_AnimInstance::Attack()
{
	if (!m_AttackEnable || Montage_IsPlaying(m_AttackMontage[m_AttackIndex]) || Montage_IsPlaying(m_AttackMontage_Enhance[m_AttackIndex]))
		return;

	m_AttackEnable = false;


	if (IsValid(m_Player)) {
		if (m_Player->IsAuraEnhanced()) {
			Montage_SetPosition(m_AttackMontage_Enhance[m_AttackIndex], 0.f);
			Montage_Play(m_AttackMontage_Enhance[m_AttackIndex]);
		}
		else {
			Montage_SetPosition(m_AttackMontage[m_AttackIndex], 0.f);
			Montage_Play(m_AttackMontage[m_AttackIndex]);
		}
	}

	m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontage.Num();
}

void UKwang_AnimInstance::Dash()
{
}

void UKwang_AnimInstance::Skill1()
{
	if (!m_Charging) {
		Montage_SetPosition(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Started)], 0.f);
		Montage_Play(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Started)]);

		m_Charging = true;
	}
}

void UKwang_AnimInstance::Skill1Canceled()
{
	m_AttackEnable = true;
	m_Charging = false;
}

void UKwang_AnimInstance::Skill1Release()
{
	if (!m_Charging)
		return;

	if (Montage_IsPlaying(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Released)]))
		return;

	Montage_SetPosition(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Released)], 0.f);
	Montage_Play(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Released)]);
}

void UKwang_AnimInstance::Skill2()
{
	if (!m_AttackEnable)
		return;

	Montage_SetPosition(m_SkillMontage[static_cast<int>(EKwangSkill::Skill2_Started)], 0.f);
	Montage_Play(m_SkillMontage[static_cast<int>(EKwangSkill::Skill2_Started)]);
}

void UKwang_AnimInstance::Skill3()
{
	if (!m_AttackEnable)
		return;

	Montage_SetPosition(m_SkillMontage[static_cast<int>(EKwangSkill::Skill3_Started)], 0.f);
	Montage_Play(m_SkillMontage[static_cast<int>(EKwangSkill::Skill3_Started)]);
}

void UKwang_AnimInstance::ActionEnable()
{
	m_AttackEnable = true;
	m_Charging = false;

	if (IsValid(m_Player)) {
		AKwang_Controller* Controller = Cast<AKwang_Controller>(m_Player->GetController());

		if(IsValid(Controller))
			Controller->MovePossible(true);
	}
}

void UKwang_AnimInstance::ActionDisable()
{
	m_AttackEnable = false;

	if (IsValid(m_Player)) {
		AKwang_Controller* Controller = Cast<AKwang_Controller>(m_Player->GetController());

		if (IsValid(Controller))
			Controller->MovePossible(false);
	}
}

void UKwang_AnimInstance::AnimNotify_Attack()
{
	if (IsValid(m_Player))
		m_Player->Attack();
}

void UKwang_AnimInstance::AnimNotify_Attack2()
{
	if (IsValid(m_Player))
		m_Player->Attack_Enhance();
}

void UKwang_AnimInstance::AnimNotify_AttackEnable()
{
	m_AttackEnable = true;
}

void UKwang_AnimInstance::AnimNotify_AttackEnd()
{
	m_AttackIndex = 0;
}

void UKwang_AnimInstance::AnimNotify_ShootEnable()
{
	Montage_SetPosition(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Charging)], 0.f);
	Montage_Play(m_SkillMontage[static_cast<int>(EKwangSkill::Skill1_Charging)]);

	// Enhanced�϶� ���� ���� �߻��ϵ��� �ش� ��Ƽ���̿� ����
	if (IsValid(m_Player)) {
		if (m_Player->IsAuraEnhanced()) {
			m_Player->Skill1_ChargeShot_ActiveSkill();
		}
	}
}

void UKwang_AnimInstance::AnimNotify_FirstCharge()
{
	// ù ��° ���� ����Ʈ ����
	// �� �ܰ迡�� ������ �ƴٸ�, ������ ������ 2�ܰ�� �Ѵ�.
	if (IsValid(m_Player))
		m_Player->AddSkill1Charge();
}

void UKwang_AnimInstance::AnimNotify_SecondCharge()
{
	// �� ��° ���� ����Ʈ ����
	// �� �ܰ迡�� ������ �ƴٸ�, ������ ������ 3(Max)�ܰ�� �Ѵ�.
	if (IsValid(m_Player)) 
		m_Player->AddSkill1Charge();
}

void UKwang_AnimInstance::AnimNotify_ChargeEnd()
{
	// ���� ��� �ð��� �Ѿ� ���� �߻�Ǵ� Ÿ�̹�.
	// Skill1Release �Լ��� ����������, �������� �߻��Ų��.
	if (IsValid(m_Player))
		m_Player->Skill1_ChargeShot_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_ChargeShoot()
{
	// �÷��̾��� ���������κ��� ���� �ܰ迡 ���� �������� �߻��ϵ��� �Ѵ�.
	if (IsValid(m_Player))
		m_Player->Skill1_ChargeShot_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_Skill2Ability()
{
	// �÷��̾� �ֺ��� ������ ���ظ� ������.
	if (IsValid(m_Player))
		m_Player->Skill2_ThunderStorm_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_Skill2Ability2()
{
	if (IsValid(m_Player))
		m_Player->Skill2_ThunderStorm_ActiveSkill_Enhance();
}

void UKwang_AnimInstance::AnimNotify_Skill3Ability()
{
	// ���⿡ N�ʰ� ���� �ο��ϸ�, ���� �ο��� ���� ���ݷ� ��ȭ.
	// ���� �׵��� ��� ������ ����Ʈ�� Ǫ�� ������ �ٲ۴�.
	if (IsValid(m_Player))
		m_Player->Skill3_ThunderAura_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_AbilityStart()
{
	ActionDisable();
}

void UKwang_AnimInstance::AnimNotify_AbilityEnd()
{
	ActionEnable();
}
