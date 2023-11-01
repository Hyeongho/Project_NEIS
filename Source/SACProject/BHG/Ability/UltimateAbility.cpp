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
		//현재 애니메이션 변경이 가능한상태인지 먼저 확인. 애니메이션 변경처리후에 쿨타임을 적용해야한다. 
		bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

		//애니메이션 변경불가상태라면 더이상 실행하지않는다. 
		if (!AttackEnable)
			return;

		FVector FwdLoc = OwnerComp->GetOwner()->GetActorForwardVector();
		FwdLoc *= 350.f;

		FVector OwnerLoc = OwnerComp->GetOwner()->GetActorLocation();
		FRotator OwnerRot = OwnerComp->GetOwner()->GetActorRotation();


		GetWorld()->SpawnActor<ADefaultSpawnObject>(m_ShadowSpawner, OwnerLoc + FwdLoc, OwnerRot);

		m_AbilityActive = false;

		//쿨타임을 등록한다. 
		AbilityCoolTimeActivated();
	}

}

void UUltimateAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

		if (EventName == TEXT("DamagedUltimate"))
		{
			// Damage를 받을 대상에게 전달. 		
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
