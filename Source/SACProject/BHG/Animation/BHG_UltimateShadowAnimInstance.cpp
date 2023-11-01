// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_UltimateShadowAnimInstance.h"
#include "../../Player/PlayerCharacter.h"
#include "../Player/BHG_UltimateShadow.h"
#include "../SpawnObject/ShadowSpawnObject.h"

UBHG_UltimateShadowAnimInstance::UBHG_UltimateShadowAnimInstance()
	: Super()
{
	m_AnimType = EUltimateShadowAnimType::Start;
}

void UBHG_UltimateShadowAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBHG_UltimateShadowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
}

void UBHG_UltimateShadowAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBHG_UltimateShadowAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBHG_UltimateShadowAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBHG_UltimateShadowAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBHG_UltimateShadowAnimInstance::AnimNotify_RespawnEnd()
{
	m_AnimType = EUltimateShadowAnimType::Active;
}

void UBHG_UltimateShadowAnimInstance::AnimNotify_UltimateStart()
{
	ABHG_UltimateShadow* OwnerCharacter = Cast<ABHG_UltimateShadow>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		AShadowSpawnObject* Spawner = Cast<AShadowSpawnObject>(OwnerCharacter->GetShadowOwnerActor());

		if(IsValid(Spawner))
			Spawner->UltimateSkillStart();
	}
}

void UBHG_UltimateShadowAnimInstance::AnimNotify_UltimateEnd()
{
	m_AnimType = EUltimateShadowAnimType::End;
}

void UBHG_UltimateShadowAnimInstance::AnimNotify_UltimateDestory()
{
	ABHG_UltimateShadow* OwnerCharacter = Cast<ABHG_UltimateShadow>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->SetDestorySpawner();
		OwnerCharacter->Destroy();
	}
}

void UBHG_UltimateShadowAnimInstance::AnimNotify_UltimateEffect()
{
	ABHG_UltimateShadow* OwnerCharacter = Cast<ABHG_UltimateShadow>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->SetDestoryEffect();
	}
}
