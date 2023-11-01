// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_AIAnimInstance.h"
#include "../../AI/AICharacter.h"
#include "../Component/AbilityComponent.h"
#include "../AI/AI_Monster.h"

UBHG_AIAnimInstance::UBHG_AIAnimInstance()
	: Super()
{
	m_AnimType = EAIMonsterAnimType::Respawn;

	m_HitEnable = false;
}

void UBHG_AIAnimInstance::SetAnimType(EAIMonsterAnimType Type)
{
	if (m_AnimType == EAIMonsterAnimType::Die)
		return;

	m_AnimType = Type;
}

void UBHG_AIAnimInstance::SetHitEnable(bool Enable)
{
	if (m_AnimType != EAIMonsterAnimType::Die)
	m_HitEnable = true;
}

void UBHG_AIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBHG_AIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBHG_AIAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBHG_AIAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBHG_AIAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBHG_AIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBHG_AIAnimInstance::AIDefaultAttack()
{	
	if (m_AnimType != EAIMonsterAnimType::Die)
	{
		m_AnimType = EAIMonsterAnimType::Attack;

		AAI_Monster* AIMonster = Cast<AAI_Monster>(TryGetPawnOwner());

		m_HitEnable = false;
	}
	
}

void UBHG_AIAnimInstance::AnimNotify_RespawnEnd()
{
	if (m_AnimType != EAIMonsterAnimType::Die)
	m_AnimType = EAIMonsterAnimType::Idle;
}

void UBHG_AIAnimInstance::AnimNotify_HitEnd()
{
	if (m_AnimType != EAIMonsterAnimType::Die)
	m_HitEnable = false;
}

void UBHG_AIAnimInstance::AnimNotify_HitBoxCreate()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateDefaultHitBox"), TryGetPawnOwner(),nullptr);
}

void UBHG_AIAnimInstance::AnimNotify_HitBoxDestroy()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroyDefaultHitBox"), TryGetPawnOwner(),nullptr);


}

void UBHG_AIAnimInstance::AnimNotify_AttackEnd()
{
	if (m_AnimType != EAIMonsterAnimType::Die)
	m_HitEnable = false;
}

void UBHG_AIAnimInstance::AnimNotify_RecoveryEnd()
{
	if (m_AnimType != EAIMonsterAnimType::Die)
	{
		m_AnimType = EAIMonsterAnimType::Idle;

		m_HitEnable = false;
	}
}

void UBHG_AIAnimInstance::AnimNotify_Death()
{
	AAI_Monster* OwnerCharacter = Cast<AAI_Monster>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->Destroy();
}
