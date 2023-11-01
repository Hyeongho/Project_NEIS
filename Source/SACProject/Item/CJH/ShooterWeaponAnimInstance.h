// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "ShooterWeaponAnimInstance.generated.h"

class AShooterWeapon;
class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UShooterWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UShooterWeaponAnimInstance();

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

	void UpdateAnimationProperties(float DeltaSeconds);

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterWeapon> m_ShooterWeapon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterCharacter> m_ShooterCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_MovingClip;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	FTransform m_HandSceneCompTransform;
};
