// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMonsterAnimInstance.h"
#include "ShooterMonster.h"

UShooterMonsterAnimInstance::UShooterMonsterAnimInstance()
	: Super()
{
}

void UShooterMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!IsValid(m_ShooterMonster))
		m_ShooterMonster = Cast<AShooterMonster>(TryGetPawnOwner());
}

void UShooterMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperty(DeltaSeconds);
}

void UShooterMonsterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UShooterMonsterAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UShooterMonsterAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UShooterMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UShooterMonsterAnimInstance::UpdateAnimationProperty(float DeltaSeconds)
{
	if (!IsValid(m_ShooterMonster))
		m_ShooterMonster = Cast<AShooterMonster>(TryGetPawnOwner());

	if (IsValid(m_ShooterMonster))
	{
		FVector Velocity = m_ShooterMonster->GetVelocity();
		Velocity.Z = 0.0f;
		m_Speed = Velocity.Size();
	}
}

void UShooterMonsterAnimInstance::AnimNotify_ResetStun()
{
	if (IsValid(m_ShooterMonster))
		m_ShooterMonster->ResetStun();
}

void UShooterMonsterAnimInstance::AnimNotify_ResetCanAttack()
{
	//if (IsValid(m_ShooterMonster))
	//	m_ShooterMonster->SetCanAttack(true);
}

void UShooterMonsterAnimInstance::AnimNotify_SpawnHitBox()
{
	if (IsValid(m_ShooterMonster))
		m_ShooterMonster->SpawnHitBox();
}

void UShooterMonsterAnimInstance::AnimNotify_SpawnProjectile()
{
	if (IsValid(m_ShooterMonster))
		m_ShooterMonster->SpawnProjectile();
}

void UShooterMonsterAnimInstance::AnimNotify_Die()
{
	if (IsValid(m_ShooterMonster))
		m_ShooterMonster->Die();
}
