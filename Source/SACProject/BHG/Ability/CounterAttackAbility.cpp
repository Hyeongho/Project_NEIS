// Fill out your copyright notice in the Description page of Project Settings.


#include "CounterAttackAbility.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Component/AbilityComponent.h"
#include "../Collider/HitBoxObject.h"
#include "../AI/DefaultAICharacter.h"

UCounterAttackAbility::UCounterAttackAbility()
	: Super()
{
	m_AbilityName = TEXT("CounterAttack");

	m_CounterAbility = true;
}

void UCounterAttackAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	if (m_AbilityActive)
	{
		//현재 애니메이션 변경이 가능한상태인지 먼저 확인. 애니메이션 변경처리후에 쿨타임을 적용해야한다. 
		bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

		//현재 플레이어가 이동중인지 확인한다. 
		bool MoveEnable = OwnerComp->GetMoveEnable();

		//다른애니메이션이 동작하고 있거나, 이동중이라면 어빌리티를 실행하지 않는다. 
		if (!AttackEnable || !MoveEnable)
			return;

		//사용중 이동이 불가하도록 한다. 
		OwnerComp->SetMoveLockEnable(true);

		Cast<UBHG_PlayerAnimInstance>(AnimInstance)->CounterAttack();	

		m_AbilityActive = false;

		//쿨타임을 등록한다. 
		AbilityCoolTimeActivated();
	}
}

void UCounterAttackAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("CreateCounterHitBox"))
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);

		if (IsValid(OwnerCharacter))
		{		
				
			FVector OwnerFwdLoc = OwnerCharacter->GetActorForwardVector();
			OwnerFwdLoc *= 75.f;

			if (IsValid(m_AbilityHitBox))
			{
				FActorSpawnParameters ActorParams;
				ActorParams.Owner = OwnerCharacter;

				m_AbilityHitBoxObj = GetWorld()->SpawnActor<AHitBoxObject>(m_AbilityHitBox,
					OwnerCharacter->GetActorLocation() + OwnerFwdLoc,
							FRotator::ZeroRotator, ActorParams);		

				m_AbilityHitBoxObj->SetShooter(OwnerCharacter);

			
							
			}				
			
		}
	}

	else if (EventName == TEXT("DestroyCounterHitBox"))
	{
		m_AbilityHitBoxObj->HitBoxDestroy();
	}

	else if (EventName == TEXT("DamagedCounterAttack"))
	{
		ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

		if (IsValid(AITarget))
			AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}

}

void UCounterAttackAbility::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);

	OwnerComp->SetMoveLockEnable(false);
}

void UCounterAttackAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();

}

void UCounterAttackAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UCounterAttackAbility::AbilityActiveOn, m_AbilityCoolTime, false);

}
