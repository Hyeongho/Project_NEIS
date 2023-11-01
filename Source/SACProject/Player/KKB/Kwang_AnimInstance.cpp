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

	// Enhanced일때 차지 없이 발사하도록 해당 노티파이에 설정
	if (IsValid(m_Player)) {
		if (m_Player->IsAuraEnhanced()) {
			m_Player->Skill1_ChargeShot_ActiveSkill();
		}
	}
}

void UKwang_AnimInstance::AnimNotify_FirstCharge()
{
	// 첫 번째 차지 이펙트 실행
	// 이 단계에서 릴리즈 됐다면, 차지샷 범위를 2단계로 한다.
	if (IsValid(m_Player))
		m_Player->AddSkill1Charge();
}

void UKwang_AnimInstance::AnimNotify_SecondCharge()
{
	// 두 번째 차지 이펙트 실행
	// 이 단계에서 릴리즈 됐다면, 차지샷 범위를 3(Max)단계로 한다.
	if (IsValid(m_Player)) 
		m_Player->AddSkill1Charge();
}

void UKwang_AnimInstance::AnimNotify_ChargeEnd()
{
	// 차지 대기 시간을 넘어 강제 발사되는 타이밍.
	// Skill1Release 함수를 강제실행해, 차지샷을 발사시킨다.
	if (IsValid(m_Player))
		m_Player->Skill1_ChargeShot_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_ChargeShoot()
{
	// 플레이어의 포지션으로부터 차지 단계에 따른 차지샷을 발사하도록 한다.
	if (IsValid(m_Player))
		m_Player->Skill1_ChargeShot_ActiveSkill();
}

void UKwang_AnimInstance::AnimNotify_Skill2Ability()
{
	// 플레이어 주변에 광범위 피해를 입힌다.
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
	// 무기에 N초간 오라를 부여하며, 오라가 부여된 동안 공격력 강화.
	// 또한 그동안 모든 공격의 이펙트를 푸른 색으로 바꾼다.
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
