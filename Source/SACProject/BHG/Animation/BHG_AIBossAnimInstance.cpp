// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_AIBossAnimInstance.h"
#include "../../AI/AICharacter.h"
#include "../Component/AbilityComponent.h"
#include "../AI/AI_BossMonster.h"

UBHG_AIBossAnimInstance::UBHG_AIBossAnimInstance()
	: Super()
{
	m_IdleBattle = false;
	m_CounterSuccess = false;

	m_AnimType = EAIBossMonsterAnimType::Respawn;
}

void UBHG_AIBossAnimInstance::SetAnimType(EAIBossMonsterAnimType Type)
{
	if (Type == EAIBossMonsterAnimType::Die)
		m_AnimType = Type;


	if (m_AnimType == EAIBossMonsterAnimType::Die)
		return;

	if(m_AnimType == EAIBossMonsterAnimType::Idle || m_AnimType == EAIBossMonsterAnimType::Run)
	m_AnimType = Type;
}

void UBHG_AIBossAnimInstance::SetCounterSuccess(bool Success)
{
	m_CounterSuccess = Success;
}

const bool& UBHG_AIBossAnimInstance::GetCounterSuccess() const
{
	return m_CounterSuccess;
}

EAIBossMonsterAnimType UBHG_AIBossAnimInstance::GetBossAnimType()
{
	return m_AnimType;
}

void UBHG_AIBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBHG_AIBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(m_AnimType == EAIBossMonsterAnimType::Idle)
		m_CounterSuccess = false;
}

void UBHG_AIBossAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBHG_AIBossAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBHG_AIBossAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBHG_AIBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBHG_AIBossAnimInstance::DefaultAttack1()
{
	m_AnimType = EAIBossMonsterAnimType::Attack1;
}

void UBHG_AIBossAnimInstance::DefaultAttack2()
{
	m_AnimType = EAIBossMonsterAnimType::Attack2;
}

void UBHG_AIBossAnimInstance::Skill1()
{
	m_AnimType = EAIBossMonsterAnimType::Skill1;
}

void UBHG_AIBossAnimInstance::Skill2()
{	
	m_AnimType = EAIBossMonsterAnimType::Skill2;
}

void UBHG_AIBossAnimInstance::AnimNotify_Idle()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack1CounterEnd"), TryGetPawnOwner(), nullptr);

		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);

		Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_StandIdle()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack1CounterEnd"), TryGetPawnOwner(), nullptr);

		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);

		Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_RespawnEnd()
{
	m_AnimType = EAIBossMonsterAnimType::Idle;

	AAI_BossMonster* OwnerCharacter = Cast<AAI_BossMonster>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->SetRespawnOn();
	}

	
}

void UBHG_AIBossAnimInstance::AnimNotify_DefaultAttack1Counter()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack1CounterStart"), TryGetPawnOwner(), nullptr);

		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0),true);
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_DefaultAttackEnd()
{
	m_IdleBattle = true;

	m_AnimType = EAIBossMonsterAnimType::Idle;

	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack1CounterEnd"), TryGetPawnOwner(), nullptr);

		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);

		Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_Attack2CounterStart()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack2CounterStart"), TryGetPawnOwner(), nullptr);
		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), true);
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_DefaultAttack2End()
{
	m_IdleBattle = false;

	m_AnimType = EAIBossMonsterAnimType::Idle;

	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());


	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DefaultAttack2CounterEnd"), TryGetPawnOwner(), nullptr);
		Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);
		Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_Skill1End()
{
	m_IdleBattle = false;

	m_AnimType = EAIBossMonsterAnimType::Idle;

	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
}

void UBHG_AIBossAnimInstance::AnimNotify_Skill1CounterAttackStart()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("Skill1CounterAttackStart"), TryGetPawnOwner(), nullptr);

	Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), true);
}

void UBHG_AIBossAnimInstance::AnimNotify_Skill1CounterAttackEnd()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("Skill1CounterAttackEnd"), TryGetPawnOwner(), nullptr);

	Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);
}

void UBHG_AIBossAnimInstance::AnimNotify_GrogyEnd()
{
	m_IdleBattle = false;
	m_AnimType = EAIBossMonsterAnimType::Idle;

	m_CounterSuccess = false;

	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("Skill1CounterAttackEnd"), TryGetPawnOwner(), nullptr);

	Cast<AAI_BossMonster>(OwnerCharacter)->SetCharacterGlow(FVector(0.265, 0.258, 1.0), false);
	Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();

}

void UBHG_AIBossAnimInstance::AnimNotify_Skill1Start()
{
	m_CounterSuccess = false;
}

void UBHG_AIBossAnimInstance::AnimNotify_Skill1EffectStart()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("Skill1EffectStart"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_RockCreate()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("RockCreate"), TryGetPawnOwner(), nullptr);		
	}
}

void UBHG_AIBossAnimInstance::AnimNotify_DecalCreate()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DecalCreate"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_Skill2End()
{
	m_IdleBattle = false;
	m_AnimType = EAIBossMonsterAnimType::Idle;

	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());
	if (IsValid(OwnerCharacter))
	Cast<AAI_BossMonster>(OwnerCharacter)->BossAbilityEnd();
}

void UBHG_AIBossAnimInstance::AnimNotify_CreateDefaultAttackHitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateDefaultAttackHitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_DestroyDefaultAttackHitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroyDefaultAttackHitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_CreateDefaultAttack1HitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateDefaultAttack1HitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_DestroyDefaultAttack1HitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroyDefaultAttack1HitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_CreateSkill2HitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateSkill2HitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_AIBossAnimInstance::AnimNotify_DestroySkill2HitBox()
{
	AAICharacter* OwnerCharacter = Cast<AAICharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroySkill2HitBox"), TryGetPawnOwner(), nullptr);
}
