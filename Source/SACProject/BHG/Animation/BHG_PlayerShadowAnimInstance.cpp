// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_PlayerShadowAnimInstance.h"
#include "../Player/BHG_ShadowPlayer.h"

UBHG_PlayerShadowAnimInstance::UBHG_PlayerShadowAnimInstance()
	: Super()
{
	m_AnimType = EShadowAnimType::Respawn;
}

void UBHG_PlayerShadowAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBHG_PlayerShadowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBHG_PlayerShadowAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBHG_PlayerShadowAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBHG_PlayerShadowAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBHG_PlayerShadowAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBHG_PlayerShadowAnimInstance::DefaultAttack()
{
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	mAttackEnable = false;

	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	Montage_Play(mAttackMontage[mAttackIndex]);

	mAttackIndex = (mAttackIndex + 1) % mAttackMontage.Num();
}

void UBHG_PlayerShadowAnimInstance::ShurikenAttack()
{
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	mAttackEnable = false;

	Montage_SetPosition(mShurikenMontage[0], 0.f);

	Montage_Play(mShurikenMontage[0]);
}

void UBHG_PlayerShadowAnimInstance::SetShadowAnimType(EShadowAnimType Type)
{
	m_AnimType = EShadowAnimType::RespawnEnd;
}

void UBHG_PlayerShadowAnimInstance::AnimNotify_RespawnEnd()
{
	m_AnimType = EShadowAnimType::Default;
}

void UBHG_PlayerShadowAnimInstance::AnimNotify_ShadowRespawnEnd()
{
	ABHG_ShadowPlayer* Shadow = Cast<ABHG_ShadowPlayer>(TryGetPawnOwner());

	if (IsValid(Shadow))
		Shadow->Destroy();
}
