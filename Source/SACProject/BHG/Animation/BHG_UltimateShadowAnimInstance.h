// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Player/PlayerAnimInstance.h"
#include "BHG_UltimateShadowAnimInstance.generated.h"



UENUM(BlueprintType)
enum class EUltimateShadowAnimType : uint8
{
	Start,
	Active,
	End,
};

UCLASS()
class SACPROJECT_API UBHG_UltimateShadowAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

public:
	UBHG_UltimateShadowAnimInstance();

protected:
	UPROPERTY(Category = "AnimType", EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"));
	EUltimateShadowAnimType m_AnimType;


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
	UFUNCTION()
		void AnimNotify_RespawnEnd();

	UFUNCTION()
		void AnimNotify_UltimateStart();

	UFUNCTION()
		void AnimNotify_UltimateEnd();

	UFUNCTION()
		void AnimNotify_UltimateDestory();

	UFUNCTION()
		void AnimNotify_UltimateEffect();

	
};
