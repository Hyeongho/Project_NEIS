// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIAnimInstance.h"
#include "IS_AIAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UIS_AIAnimInst : public UDefaultAIAnimInstance
{
	GENERATED_BODY()

public:
	UIS_AIAnimInst();

protected:
	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly)
	bool		m_HitEnable;

protected:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

public:
	inline EAIAnimType GetAnimType() const;
	inline void SetHitEnable(bool HitEnable = true) { m_HitEnable = HitEnable; }
	inline void SetDeath() { m_AnimType = EAIAnimType::Death; }

private:
	UFUNCTION()
	void AnimNotify_StartEnd();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_DeathDissStart();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	// walk
	UFUNCTION()
	void AnimNotify_LeftPlan();

	UFUNCTION()
	void AnimNotify_RightPlan();
};
