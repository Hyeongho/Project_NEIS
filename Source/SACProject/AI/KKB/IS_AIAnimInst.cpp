// Fill out your copyright notice in the Description page of Project Settings.


#include "IS_AIAnimInst.h"
#include "IS_AIController.h"
#include "IS_AICharacter.h"

UIS_AIAnimInst::UIS_AIAnimInst() :
	m_HitEnable(false)
{
}

void UIS_AIAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UIS_AIAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UIS_AIAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UIS_AIAnimInst::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UIS_AIAnimInst::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UIS_AIAnimInst::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

EAIAnimType UIS_AIAnimInst::GetAnimType() const
{
	return m_AnimType;
}

void UIS_AIAnimInst::AnimNotify_StartEnd()
{
	m_AnimType = EAIAnimType::Idle;

	AIS_AICharacter* ISCharacter = Cast<AIS_AICharacter>(TryGetPawnOwner());

	if (IsValid(ISCharacter)) {
		AIS_AIController* AIController = Cast<AIS_AIController>(ISCharacter->GetController());

		if (IsValid(AIController))
			AIController->SetStartToBB();
	}
}

void UIS_AIAnimInst::AnimNotify_AttackEnd()
{
	m_AnimType = EAIAnimType::Idle;
}

void UIS_AIAnimInst::AnimNotify_HitEnd()
{
	m_HitEnable = false;
}

void UIS_AIAnimInst::AnimNotify_DeathDissStart()
{
	AIS_AICharacter* ISCharacter = Cast<AIS_AICharacter>(TryGetPawnOwner());

	if (IsValid(ISCharacter))
		ISCharacter->DeathEnd();
}

void UIS_AIAnimInst::AnimNotify_DeathEnd()
{
}

void UIS_AIAnimInst::AnimNotify_LeftPlan()
{
}

void UIS_AIAnimInst::AnimNotify_RightPlan()
{
}
