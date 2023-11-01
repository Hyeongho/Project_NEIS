// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../DefaultAIAnimInstance.h"
#include "ShooterMonsterAnimInstance.generated.h"

class AShooterMonster;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UShooterMonsterAnimInstance : public UDefaultAIAnimInstance
{
	GENERATED_BODY()

public:
	UShooterMonsterAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativePostEvaluateAnimation() override;

	virtual void NativeUninitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	void UpdateAnimationProperty(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_ResetStun();

	UFUNCTION()
	void AnimNotify_ResetCanAttack();

	UFUNCTION()
	void AnimNotify_SpawnHitBox();

	UFUNCTION()
	void AnimNotify_SpawnProjectile();

	UFUNCTION()
	void AnimNotify_Die();

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterMonster> m_ShooterMonster;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_Speed;
};
