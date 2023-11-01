// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BHG_PlayerAnimInstance.h"
#include "BHG_PlayerShadowAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EShadowAnimType : uint8
{
	Default,
	Respawn,
	RespawnEnd,
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBHG_PlayerShadowAnimInstance : public UBHG_PlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UBHG_PlayerShadowAnimInstance();

protected:
	UPROPERTY(Category = "AnimType", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	EShadowAnimType m_AnimType;

protected:
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

public:
	virtual void DefaultAttack() override;
	virtual void ShurikenAttack() override;

public:
	void SetShadowAnimType(EShadowAnimType Type);

public:
	UFUNCTION()
	void AnimNotify_RespawnEnd();

	UFUNCTION()
	void AnimNotify_ShadowRespawnEnd();
};
