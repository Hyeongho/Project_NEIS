// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_PlayerAnimInstance.h"
#include "../Player/BHG_Player.h"
#include "../../Player/PlayerCharacter.h"
#include "../Component/AbilityComponent.h"



UBHG_PlayerAnimInstance::UBHG_PlayerAnimInstance()
	: Super()
{
	mAttackEnable = true;
	mMoveEnable = true;	
	m_PlayerAnimType = EBHGPlayerAninType::Idle;
	mHitEnable = false;
}

void UBHG_PlayerAnimInstance::SetAnimType(EBHGPlayerAninType Type)
{
	m_PlayerAnimType = Type;
}

void UBHG_PlayerAnimInstance::SetHitEnable(bool Enable)
{

	if (mAttackEnable)
		mHitEnable = true;

	else
		mHitEnable = false;
}

void UBHG_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBHG_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//ABHG_Player* BHGPlayer = Cast<ABHG_Player>(TryGetPawnOwner());

	APlayerCharacter* OwnerCharacter = Cast<ABHG_Player>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		m_ForwardSpeed = OwnerCharacter->GetComponentByClass<UAbilityComponent>()->GetPlayerForwardSpeed();
		m_RightSpeed = OwnerCharacter->GetComponentByClass<UAbilityComponent>()->GetPlayerRightSpeed();
	}

}

void UBHG_PlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBHG_PlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBHG_PlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBHG_PlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBHG_PlayerAnimInstance::DefaultAttack()
{

	UE_LOG(LogTemp, Warning, TEXT("Animation Play"));

	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	mAttackEnable = false;
	
	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	Montage_Play(mAttackMontage[mAttackIndex]);

	mAttackIndex = (mAttackIndex + 1) % mAttackMontage.Num();
	
}

void UBHG_PlayerAnimInstance::ShurikenAttack()
{
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]) || Montage_IsPlaying(mNightmareMontage[0])
		|| Montage_IsPlaying(mCounterMontage[0]))
		return;

	mAttackEnable = false;

	Montage_SetPosition(mShurikenMontage[0], 0.f);
	
	Montage_Play(mShurikenMontage[0]);
}

void UBHG_PlayerAnimInstance::CounterAttack()
{
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]) || Montage_IsPlaying(mNightmareMontage[0])
		|| Montage_IsPlaying(mCounterMontage[0]))
		return;

	mAttackEnable = false;

	Montage_SetPosition(mCounterMontage[0], 0.f);

	Montage_Play(mCounterMontage[0]);

	

}

void UBHG_PlayerAnimInstance::NightmareAttack()
{
	if(!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]) || Montage_IsPlaying(mShurikenMontage[0])
		|| Montage_IsPlaying(mCounterMontage[0]))
		return;

	mAttackEnable = false;

	Montage_SetPosition(mNightmareMontage[0], 0.f);

	Montage_Play(mNightmareMontage[0]);
}

void UBHG_PlayerAnimInstance::AnimNotify_NightmareEnd()
{
	m_PlayerAnimType = EBHGPlayerAninType::Idle;
}

void UBHG_PlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	OwnerCharacter->GetComponentByClass<UAbilityComponent>()->SetMoveEnable(false);

}

void UBHG_PlayerAnimInstance::AnimNotify_Attack2()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->SetMoveEnable(false);
}

void UBHG_PlayerAnimInstance::AnimNotify_ShurikenAttack()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("ShurikenCreate"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UBHG_PlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackIndex = 0;

	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	OwnerCharacter->GetComponentByClass<UAbilityComponent>()->SetMoveEnable(true);
}

void UBHG_PlayerAnimInstance::AnimNotify_NightmareStart()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("NightmareStart"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_NightmareAttack()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("NightmareCreate"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_NightmareAttackEnd()
{
	mAttackIndex = 0;
	mAttackEnable = true;

	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->EndAbility(TEXT("Nightmare"));
}

void UBHG_PlayerAnimInstance::AnimNotify_CounterAttack()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateCounterHitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_CounterAttackEnd()
{
	mAttackIndex = 0;
	mAttackEnable = true;

	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
	{
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroyCounterHitBox"), TryGetPawnOwner(), nullptr);
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->EndAbility(TEXT("CounterAttack"));
	}

}

void UBHG_PlayerAnimInstance::AnimNotify_AttackHitBox()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("CreateDefaultHitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_AttackHitBoxEnd()
{
	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if(IsValid(OwnerCharacter))
	OwnerCharacter->GetComponentByClass<UAbilityComponent>()->ActivatedAbilityEvent(TEXT("DestroyDefaultHitBox"), TryGetPawnOwner(), nullptr);
}

void UBHG_PlayerAnimInstance::AnimNotify_PlayerHitEnd()
{
	mHitEnable = false;
}
