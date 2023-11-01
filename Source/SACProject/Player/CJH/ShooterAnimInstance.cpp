// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UShooterAnimInstance::UShooterAnimInstance()
	: m_Speed(0.0f)
	, m_Accelerating(false)
	, m_InAir(false)
	, m_MovementOffsetYaw(0.0f)
	, m_PrevMovementOffsetYaw(0.0f)
	, m_Aiming(false)
	, m_CharacterYawTIP(0.0f)
	, m_PrevCharacterYawTIP(0.0f)
	, m_RootYawOffset(0.0f)
	, m_RotationCurve(0.0f)
	, m_PrevRotationCurve(0.0f)
	, m_Pitch(0.0f)
	, m_Reloading(false)
	, m_AimOffsetState(EAimOffsetState::Hip)
	, m_CharacterRotation(FRotator(0.0f))
	, m_PrevCharacterRotation(FRotator(0.0f))
	, m_YawDelta(0.0f)
	, m_Crouching(false)
	, m_RecoilWeight(1.0f)
	, m_TurningInPlace(false)
	, m_Equipping(false)
{
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AShooterCharacter* Character = Cast<AShooterCharacter>(TryGetPawnOwner());
	if (Character)
		m_ShooterCharacter = Character;
}

void UShooterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperties(DeltaSeconds);
}

void UShooterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

}

void UShooterAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();

}

void UShooterAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();

}

void UShooterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaSeconds)
{
	if (!m_ShooterCharacter)
		m_ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());

	if (m_ShooterCharacter)
	{
		FVector Velocity = m_ShooterCharacter->GetVelocity();
		Velocity.Z = 0.0;	// Z is ignored
		m_Speed = Velocity.Size();

		UCharacterMovementComponent* MoveComp = m_ShooterCharacter->GetCharacterMovement();
		m_Accelerating = MoveComp->GetCurrentAcceleration().Size() > 0.0 ? true : false;

		m_Aiming = m_ShooterCharacter->IsAiming();
		m_InAir = m_ShooterCharacter->GetCharacterMovement()->IsFalling();
		m_Crouching = m_ShooterCharacter->IsCrouching();

		FRotator AimRotation = m_ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		m_MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (m_Speed > 0.0f)
			m_PrevMovementOffsetYaw = m_MovementOffsetYaw;

		m_Pitch = m_ShooterCharacter->GetBaseAimRotation().Pitch;

		//m_Reloading = m_ShooterCharacter->GetCombatState() == ECombatState::Reloading;
		//m_Equipping = m_ShooterCharacter->GetCombatState() == ECombatState::Equipping;

		// Set AimOffsetState
		if (m_Reloading)
			m_AimOffsetState = EAimOffsetState::Reloading;
		else if (m_InAir)
			m_AimOffsetState = EAimOffsetState::InAir;
		else if (m_Aiming)
			m_AimOffsetState = EAimOffsetState::Aiming;
		else
			m_AimOffsetState = EAimOffsetState::Hip;

		TurnInPlace();
		SetRecoilWeight();
		Lean(DeltaSeconds);
	}
}

void UShooterAnimInstance::TurnInPlace()
{
	if (m_Speed > 0 || m_InAir)
	{
		// Don't want to turn in place (Character is moving)
		m_RootYawOffset = 0.0f;
		m_CharacterYawTIP = m_ShooterCharacter->GetActorRotation().Yaw;
		m_PrevCharacterYawTIP = m_CharacterYawTIP;
		m_RotationCurve = 0.0f;
		m_PrevRotationCurve = 0.0f;
	}
	else
	{
		m_PrevCharacterYawTIP = m_CharacterYawTIP;
		m_CharacterYawTIP = m_ShooterCharacter->GetActorRotation().Yaw;
		const float YawDeltaTIP = m_CharacterYawTIP - m_PrevCharacterYawTIP;

		// update and clamp to [ -180, 180 ]
		m_RootYawOffset = UKismetMathLibrary::NormalizeAxis(m_RootYawOffset - YawDeltaTIP);

		// 1.0f if turning, 0.0f if not
		const float Turning = GetCurveValue(TEXT("Turning"));
		if (Turning > 0)
		{
			m_TurningInPlace = true;

			m_PrevRotationCurve = m_RotationCurve;
			m_RotationCurve = GetCurveValue(TEXT("Rotation"));
			float RotationDelta = m_RotationCurve - m_PrevRotationCurve;

			// RootYawOffset > 0, -> Turning Left, RootYawOffset < 0, -> Turning Right
			m_RootYawOffset > 0 ? m_RootYawOffset -= RotationDelta : m_RootYawOffset += RotationDelta;
			m_RootYawOffset = FMath::Clamp(m_RootYawOffset, -90.0f, 90.0f);

			// if turning too fast
			const float RootYawOffsetABS = FMath::Abs(m_RootYawOffset);
			if (RootYawOffsetABS > 90.0f)
			{
				const float YawExcess = RootYawOffsetABS - 90.0f;
				m_RootYawOffset > 0 ? m_RootYawOffset -= YawExcess : m_RootYawOffset += YawExcess;
			}
		}
		else
			m_TurningInPlace = false;
	}
}

void UShooterAnimInstance::SetRecoilWeight()
{
	// Set the recoil weight
	if (m_TurningInPlace)
	{
		if (m_Reloading || m_Equipping)
			m_RecoilWeight = 1.0f;
		else
			m_RecoilWeight = 0.0f;
	}
	else
	{
		if (m_Crouching)
		{
			if (m_Reloading || m_Equipping)
				m_RecoilWeight = 1.0f;
			else
				m_RecoilWeight = 0.3f;
		}
		else
		{
			if (m_Aiming || m_Reloading || m_Equipping)
				m_RecoilWeight = 1.0f;
			else
				m_RecoilWeight = 0.7f;
		}
	}
}

void UShooterAnimInstance::Lean(float DeltaSeconds)
{
	m_PrevCharacterRotation = m_CharacterRotation;
	m_CharacterRotation = m_ShooterCharacter->GetActorRotation();

	const FRotator RotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(m_CharacterRotation, m_PrevCharacterRotation);

	const float Target = RotationDelta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(m_YawDelta, Target, DeltaSeconds, 6.0f);
	m_YawDelta = FMath::Clamp(Interp, -90.0f, 90.0f);
}

void UShooterAnimInstance::AnimNotify_GrapClip()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->GrapClip();
}

void UShooterAnimInstance::AnimNotify_ReplaceClip()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->ReplaceClip();
}

void UShooterAnimInstance::AnimNotify_ReloadFinish()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->ReloadFinish();
}

void UShooterAnimInstance::AnimNotify_FinishEquip()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->SetShooterState(EShooterState::Unoccupied);
}

void UShooterAnimInstance::AnimNotify_StunFinish()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->SetShooterState(EShooterState::Unoccupied);
}

void UShooterAnimInstance::AnimNotify_DeathFinish()
{
	if (IsValid(m_ShooterCharacter))
		m_ShooterCharacter->DeathFinish();
}
