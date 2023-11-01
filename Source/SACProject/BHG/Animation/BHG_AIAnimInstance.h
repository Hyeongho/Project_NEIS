// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../../Player/PlayerAnimInstance.h"
#include "BHG_AIAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EAIMonsterAnimType : uint8
{
	Respawn,
	Idle,
	Run,
	Attack,
	Die,
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBHG_AIAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

public:
	UBHG_AIAnimInstance();

protected:
	UPROPERTY(Category = "AnimType", EditAnywhere, BlueprintReadWrite)
	EAIMonsterAnimType m_AnimType;

	UPROPERTY(Category = "HitEnable", VisibleAnywhere, BlueprintReadOnly)
	bool		m_HitEnable;


public:
	void SetAnimType(EAIMonsterAnimType Type);
	void SetHitEnable(bool Enable);

public:
	const bool& GetHitEnable() const { return m_HitEnable; }
	EAIMonsterAnimType GetMonsterAnimType() { return m_AnimType; }

protected:
	virtual void NativeInitializeAnimation();
	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	// Native Post Evaluate override point
	virtual void NativePostEvaluateAnimation();
	// Native Uninitialize override point
	virtual void NativeUninitializeAnimation();
	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay();

public:
	void AIDefaultAttack();
	

protected:
	UFUNCTION()
		void AnimNotify_RespawnEnd();

	UFUNCTION()
		void AnimNotify_HitEnd();

	UFUNCTION()
		void AnimNotify_HitBoxCreate();
	
	UFUNCTION()
		void AnimNotify_HitBoxDestroy();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_RecoveryEnd();

	UFUNCTION()
		void AnimNotify_Death();
};
