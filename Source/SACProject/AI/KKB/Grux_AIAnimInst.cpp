// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_AIAnimInst.h"
#include "Grux_AICharacter.h"
#include "Grux_AIController.h"

UGrux_AIAnimInst::UGrux_AIAnimInst()
{
	m_MoveSpeed = 0.f;
	m_AttackIndex = 0;
	m_IsStun = false;
}

void UGrux_AIAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AGrux_AICharacter* Character = Cast<AGrux_AICharacter>(TryGetPawnOwner());

	if (Character)
		m_GruxCharacter = Character;
}

void UGrux_AIAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (IsValid(m_GruxCharacter))
	{
		UCharacterMovementComponent* Movement = m_GruxCharacter->GetCharacterMovement();

		if (IsValid(Movement))
			m_MoveSpeed = Movement->Velocity.Length();
	}
}

void UGrux_AIAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UGrux_AIAnimInst::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UGrux_AIAnimInst::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UGrux_AIAnimInst::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

inline EAIAnimType UGrux_AIAnimInst::GetAnimType() const
{
	return m_AnimType;
}

void UGrux_AIAnimInst::SetStun()
{
	m_IsStun = true;
	m_AnimType = EAIAnimType::Skill2;
}

void UGrux_AIAnimInst::SetStunRelease()
{
	m_IsStun = false;
	m_AnimType = EAIAnimType::Idle;
}

void UGrux_AIAnimInst::Attack_Anim()
{
	m_AnimType = EAIAnimType::Attack;


	if (IsValid(m_GruxCharacter)) {
		Montage_SetPosition(m_AttackMontage[m_AttackIndex], 0.f);
		Montage_Play(m_AttackMontage[m_AttackIndex]);
	}

	m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontage.Num();
}

void UGrux_AIAnimInst::Skill1_DoublePain_Anim()
{
	m_AnimType = EAIAnimType::Skill1;

	//if (IsValid(m_GruxCharacter)) {
	//	Montage_SetPosition(m_Skill1_DoublePain_Montage, 0.f);
	//	Montage_Play(m_Skill1_DoublePain_Montage);
	//}
}

void UGrux_AIAnimInst::Skill2_StampedeReady_Anim()
{
	m_AnimType = EAIAnimType::Skill2;

	if (IsValid(m_GruxCharacter)) {
		Montage_SetPosition(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Start)], 0.f);
		Montage_Play(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Start)]);
	}
}

void UGrux_AIAnimInst::Skill2_StampedeRun_Anim()
{
	m_AnimType = EAIAnimType::Run;

	if (IsValid(m_GruxCharacter)) {
		Montage_SetPosition(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Run)], 0.f);
		Montage_Play(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Run)]);
	}
}

void UGrux_AIAnimInst::Skill2_StampedeAttack_Anim()
{
	m_AnimType = EAIAnimType::Skill2;

	if (IsValid(m_GruxCharacter)) {
		Montage_SetPosition(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Attack)], 0.f);
		Montage_Play(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Attack)]);
	}
}

void UGrux_AIAnimInst::Skill2_StampedeStun_Anim()
{
	m_AnimType = EAIAnimType::Skill2;

	if (IsValid(m_GruxCharacter)) {
		Montage_SetPosition(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Stun)], 0.f);
		Montage_Play(m_Skill2_Stampede_Montage[static_cast<int>(EGruxStampede::Stampede_Stun)]);
	}
}

void UGrux_AIAnimInst::Skill3_Earthquake_Anim()
{
	m_AnimType = EAIAnimType::Skill3;

	//if (IsValid(m_GruxCharacter)) {
	//	Montage_SetPosition(m_Skill3_Eearthquake_Montage, 0.f);
	//	Montage_Play(m_Skill3_Eearthquake_Montage);
	//}
}

void UGrux_AIAnimInst::AnimNotify_StartEnd()
{
	m_AnimType = EAIAnimType::Idle;

	if (IsValid(m_GruxCharacter)) {
		AGrux_AIController* AIController = Cast<AGrux_AIController>(m_GruxCharacter->GetController());

		if (IsValid(AIController))
			AIController->SetStartToBB();
	}
}

void UGrux_AIAnimInst::AnimNotify_Attack()
{
	// 어택 충돌 생성
	m_GruxCharacter->Attack_Active();
}

void UGrux_AIAnimInst::AnimNotify_Attack1End()
{
	// 공격을 이어서 진행.
	Attack_Anim();
}

void UGrux_AIAnimInst::AnimNotify_Attack2End()
{
	// 공격을 이어서 진행.
	Attack_Anim();
}

void UGrux_AIAnimInst::AnimNotify_Attack3End()
{
	// 공격을 이어서 진행.
	Attack_Anim();
}

void UGrux_AIAnimInst::AnimNotify_Attack4End()
{
	if (IsValid(m_GruxCharacter)) 
		if (m_GruxCharacter->IsBerserk()) 
			m_GruxCharacter->Skill1_DoublePain();
}

void UGrux_AIAnimInst::AnimNotify_AttackEnd()
{
	// 4회 공격을 종료.
	if (IsValid(m_GruxCharacter))
		if (!m_GruxCharacter->IsBerserk()) 
			m_AnimType = EAIAnimType::Idle;

	m_AttackIndex = 0;
}

void UGrux_AIAnimInst::AnimNotify_DoublePain_Attack()
{
	if (IsValid(m_GruxCharacter))
		m_GruxCharacter->Skill1_DoublePain_ActiveSkill();
}

void UGrux_AIAnimInst::AnimNotify_DoublePain_End()
{
	m_AnimType = EAIAnimType::Idle;
}

void UGrux_AIAnimInst::AnimNotify_ReadyEnd()
{
	if (IsValid(m_GruxCharacter))
		m_GruxCharacter->TraceTarget();
}

void UGrux_AIAnimInst::AnimNotify_Stampede_Attack()
{
	if (IsValid(m_GruxCharacter))
		m_GruxCharacter->Skill2_Stampede_Attack_ActiveSkill();
}

void UGrux_AIAnimInst::AnimNotify_Stampede_End()
{
	m_AnimType = EAIAnimType::Idle;
}

void UGrux_AIAnimInst::AnimNotify_Earthquake()
{
	if(IsValid(m_GruxCharacter))
		m_GruxCharacter->Skill3_Earthquake_ActiveSkill();
}

void UGrux_AIAnimInst::AnimNotify_Earthquake_End()
{
	m_AnimType = EAIAnimType::Idle;
}
