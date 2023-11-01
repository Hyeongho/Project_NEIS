// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossSkill1Ability.h"
#include "../../Component/AbilityComponent.h"
#include "../../Animation/BHG_AIBossAnimInstance.h"
#include "../../AI/AI_BossMonster.h"
#include "../../SpawnObject/DefaultSpawnObject.h"
#include "../../Effect/BaseEffect.h"
#include "../../Player/BHG_Player.h"


UAIBossSkill1Ability::UAIBossSkill1Ability() 
	: Super()
{
	m_AbilityName = TEXT("AIBossSkill1");
}

void UAIBossSkill1Ability::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(OwnerComp->GetOwner());

	if (m_AbilityActive)
	{

		if (IsValid(BossCharacter))
		{
			UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(BossCharacter->GetMesh()->GetAnimInstance());

			if (IsValid(BossAnim))
			{
				BossAnim->Skill1();
			}


			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();
		}
	}
}

void UAIBossSkill1Ability::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("Skill1CounterAttackStart"))
	{
		//Owner의 상태를 카운터상태로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(true);

	}

	else if (EventName == TEXT("Skill1CounterAttackEnd"))
	{
		//Owner의 상태를 카운터비활성화로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(false);
	}

	else if (EventName == TEXT("RockCreate"))
	{
		GetWorld()->SpawnActor<ADefaultSpawnObject>(BossRockSpawnObj, FVector(-130, -70, -290), FRotator::ZeroRotator);
	}

	else if (EventName == TEXT("Skill1EffectStart"))
	{
		FVector OwnerDownLoc = Owner->GetActorUpVector() * -200.f;


		GetWorld()->SpawnActor<ABaseEffect>(Skill1Effect, Owner->GetActorLocation() + OwnerDownLoc, Owner->GetActorRotation());
	}

	else if (EventName == TEXT("DamagedBossSkill1"))
	{
		ABHG_Player* BHGPlayer = Cast<ABHG_Player>(Target);

		if (IsValid(BHGPlayer))
			BHGPlayer->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}


}

void UAIBossSkill1Ability::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
}

void UAIBossSkill1Ability::AbilityActiveOn()
{
	Super::AbilityActiveOn();

	GetWorld()->GetTimerManager().ClearTimer(m_AbilityTimerHandle);
}

void UAIBossSkill1Ability::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UAIBossSkill1Ability::AbilityActiveOn, m_AbilityCoolTime, false);
}
