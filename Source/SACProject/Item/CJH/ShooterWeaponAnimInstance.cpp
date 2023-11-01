// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterWeaponAnimInstance.h"
#include "ShooterWeapon.h"
#include "../../Player/CJH/ShooterCharacter.h"

UShooterWeaponAnimInstance::UShooterWeaponAnimInstance()
	: Super()
{
}

void UShooterWeaponAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_ShooterWeapon = Cast<AShooterWeapon>(GetOwningActor());
	m_ShooterCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void UShooterWeaponAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperties(DeltaSeconds);
}

void UShooterWeaponAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UShooterWeaponAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UShooterWeaponAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UShooterWeaponAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UShooterWeaponAnimInstance::UpdateAnimationProperties(float DeltaSeconds)
{
	if (IsValid(m_ShooterWeapon))
	{
		if (IsValid(m_ShooterCharacter))
		{
			m_MovingClip = m_ShooterWeapon->GetMovingClip();
			if (m_MovingClip)
			{
				m_HandSceneCompTransform = m_ShooterCharacter->GetHandSceneComponent()->GetComponentTransform();
			}
		}
		else
		{
			m_ShooterCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		}
	}
	else
	{
		m_ShooterWeapon = Cast<AShooterWeapon>(GetOwningActor());
	}
}
