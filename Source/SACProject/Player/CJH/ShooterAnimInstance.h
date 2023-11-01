// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../PlayerAnimInstance.h"
#include "ShooterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EAimOffsetState : uint8
{
	Hip			UMETA(DisplayName = "Hip"),
	Aiming		UMETA(DisplayName = "Aiming"),
	Reloading	UMETA(DisplayName = "Reloading"),
	InAir		UMETA(DisplayName = "InAir"),

	MAX			UMETA(DisplayName = "DefaultMAX")
};

class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UShooterAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

public:
	UShooterAnimInstance();

protected:
	// the below functions are the native overrides for each phase
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	// Native Post Evaluate override point
	virtual void NativePostEvaluateAnimation() override;

	// Native Uninitialize override point
	virtual void NativeUninitializeAnimation() override;

	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;

protected:
	/* Update AnimInstance properties */
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaSeconds);

	/* Handle turning in place variables */
	void TurnInPlace();

	void SetRecoilWeight();

	/* Handle Calculations for leaning while running */
	void Lean(float DeltaSeconds);

	UFUNCTION()
	void AnimNotify_GrapClip();

	UFUNCTION()
	void AnimNotify_ReplaceClip();

	UFUNCTION()
	void AnimNotify_ReloadFinish();

	UFUNCTION()
	void AnimNotify_FinishEquip();

	UFUNCTION()
	void AnimNotify_StunFinish();

	UFUNCTION()
	void AnimNotify_DeathFinish();
	

private:

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterCharacter>	m_ShooterCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_Speed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_Accelerating;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_InAir;

	/* Offset Yaw used for strafing */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MovementOffsetYaw;

	/* Offset Yaw, The frame before we stopped moving */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_PrevMovementOffsetYaw;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_Aiming;

	/* Yaw of the Character this frame for turn in place */
	float m_CharacterYawTIP;

	/* Yaw of the Character previous frame for turn in place */
	float m_PrevCharacterYawTIP;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_RootYawOffset;

	/* Rotation curve value this frame */
	float m_RotationCurve;

	/* Rotation curve value previous frame */
	float m_PrevRotationCurve;

	/* The pitch of the aim rotation, used for Aim Offset */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_Pitch;

	/* True when reloading, use to prevent Aim Offset while reloading */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_Reloading;

	/* Offset state, used to determine which Aim Offset to use */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	EAimOffsetState m_AimOffsetState;

	/* Character Yaw this frame */
	FRotator m_CharacterRotation;

	/* Character Yaw previous frame */
	FRotator m_PrevCharacterRotation;

	/* Yaw delta used for leaning in the running blendspace */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_YawDelta;

	/* True when crouching */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_Crouching;

	/* Change the recoil weight based on turning in place and aiming */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_RecoilWeight;

	/* True when turning in place */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_TurningInPlace;

	/* True when equipping */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_Equipping;
};
