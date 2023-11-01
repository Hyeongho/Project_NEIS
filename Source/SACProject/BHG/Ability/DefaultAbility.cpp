// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAbility.h"
#include "TimerManager.h"
#include "../Animation/BHG_PlayerAnimInstance.h"

UDefaultAbility::UDefaultAbility()
	: Super()
{

	m_AbilityName = TEXT("DefaultAbility");
	m_AbilityCoolTime = 0.f;
	m_AbilityActive = true;
	m_CounterAbility = false;
	m_AbilityTimerActive = false;
}

const FName& UDefaultAbility::GetAbilityName() const
{
	return m_AbilityName;
}

float UDefaultAbility::GetAbilityCoolTime()
{		
		
	float RemainTime = GetWorld()->GetTimerManager().GetTimerRemaining(m_AbilityTimerHandle);

	if (RemainTime < 0.f)
		RemainTime = 0.f;

	return RemainTime;

}

float UDefaultAbility::GetOriginCoolTime()
{
	return m_AbilityCoolTime;
}

const bool& UDefaultAbility::GetAbilityActive() const
{
	return m_AbilityActive;
}

void UDefaultAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	// Ability의 실행부

}

void UDefaultAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	// Abiltiy 실행 이후 후처리 Event
}

void UDefaultAbility::EndAbility(class UAbilityComponent* OwnerComp)
{
	// Ability 종료
}


void UDefaultAbility::AbilityActiveOn()
{
	m_AbilityActive = true;
}

void UDefaultAbility::AbilityCoolTimeActivated()
{	
	// 하위클래스별로 등록
}
