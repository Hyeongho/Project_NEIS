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
		//���� �ִϸ��̼� ������ �����ѻ������� ���� Ȯ��. �ִϸ��̼� ����ó���Ŀ� ��Ÿ���� �����ؾ��Ѵ�. 
		bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

		//���� �÷��̾ �̵������� Ȯ���Ѵ�. 
		bool MoveEnable = OwnerComp->GetMoveEnable();

		//�ٸ��ִϸ��̼��� �����ϰ� �ְų�, �̵����̶�� �����Ƽ�� �������� �ʴ´�. 
		if (!AttackEnable || !MoveEnable)
			return;

		//����� �̵��� �Ұ��ϵ��� �Ѵ�. 
		OwnerComp->SetMoveLockEnable(true);

		Cast<UBHG_PlayerAnimInstance>(AnimInstance)->CounterAttack();	

		m_AbilityActive = false;

		//��Ÿ���� ����Ѵ�. 
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
