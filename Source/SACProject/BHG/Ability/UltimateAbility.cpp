// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateAbility.h"
#include "../SpawnObject/DefaultSpawnObject.h"
#include "../Component/AbilityComponent.h"
#include "../Player/BHG_Player.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../AI/DefaultAICharacter.h"

UUltimateAbility::UUltimateAbility()
	: Super()
{
	m_AbilityName = TEXT("Ultimate");
}

void UUltimateAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	if (m_AbilityActive)
	{
		//���� �ִϸ��̼� ������ �����ѻ������� ���� Ȯ��. �ִϸ��̼� ����ó���Ŀ� ��Ÿ���� �����ؾ��Ѵ�. 
		bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

		//�ִϸ��̼� ����Ұ����¶�� ���̻� ���������ʴ´�. 
		if (!AttackEnable)
			return;

		FVector FwdLoc = OwnerComp->GetOwner()->GetActorForwardVector();
		FwdLoc *= 350.f;

		FVector OwnerLoc = OwnerComp->GetOwner()->GetActorLocation();
		FRotator OwnerRot = OwnerComp->GetOwner()->GetActorRotation();


		GetWorld()->SpawnActor<ADefaultSpawnObject>(m_ShadowSpawner, OwnerLoc + FwdLoc, OwnerRot);

		m_AbilityActive = false;

		//��Ÿ���� ����Ѵ�. 
		AbilityCoolTimeActivated();
	}

}

void UUltimateAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

		if (EventName == TEXT("DamagedUltimate"))
		{
			// Damage�� ���� ��󿡰� ����. 		
			ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

			if (IsValid(AITarget))
				AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}
}

void UUltimateAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();

	GetWorld()->GetTimerManager().ClearTimer(m_AbilityTimerHandle);
}

void UUltimateAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UUltimateAbility::AbilityActiveOn, m_AbilityCoolTime, false);
}
