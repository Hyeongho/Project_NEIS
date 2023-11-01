// Fill out your copyright notice in the Description page of Project Settings.


#include "EvadeAbility.h"
#include "../Component/AbilityComponent.h"
#include "../Player/BHG_Player.h"
#include "../../Player/DefaultPlayerState.h"

UEvadeAbility::UEvadeAbility()
	: Super()
{
	m_AbilityName = TEXT("Evade");
}

void UEvadeAbility::SetGhostOff()
{
	if (IsValid(m_OwnerCharacter))
		m_OwnerCharacter->SetEvadeOn(false);

	GetWorld()->GetTimerManager().ClearTimer(EvadeTimerHandle);
}

void UEvadeAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	m_OwnerCharacter = Cast<ABHG_Player>(OwnerComp->GetOwner());

	if (m_AbilityActive)
	{
		if (IsValid(m_OwnerCharacter))
		{
			FVector OwnerVelocity = m_OwnerCharacter->GetVelocity();
			OwnerVelocity.Z = 0.f;

			OwnerVelocity.Normalize();

			ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(m_OwnerCharacter->GetPlayerState());

			if (IsValid(DefaultPlayerState))
			{
				int32 CurruntMp = DefaultPlayerState->GetMP();

				if (CurruntMp < 200)
					return;

				DefaultPlayerState->AddMP(-200);
			}

			m_OwnerCharacter->PlayAudio();
			m_OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("AI"));
			m_OwnerCharacter->LaunchCharacter(OwnerVelocity * 4500.f, false, false);
			m_OwnerCharacter->SetEvadeOn(true);

			GetWorld()->GetTimerManager().SetTimer(EvadeTimerHandle, this, &UEvadeAbility::SetGhostOff, 0.5f, false);

			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();

		}
	}
}

void UEvadeAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("EvadeOff"))
	{	
		if (IsValid(m_OwnerCharacter))
		{
			m_OwnerCharacter->SetEvadeOn(false);
		
		}
	}
}

void UEvadeAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();


}

void UEvadeAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UEvadeAbility::AbilityActiveOn, m_AbilityCoolTime, false);
	
}
