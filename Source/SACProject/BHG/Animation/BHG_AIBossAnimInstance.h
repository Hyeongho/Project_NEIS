// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Player/PlayerAnimInstance.h"
#include "BHG_AIBossAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EAIBossMonsterAnimType : uint8
{
	Respawn,
	CutScene,
	Idle,
	Run,
	Attack1,
	Attack2,
	Skill1,
	Skill2,
	Die,
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBHG_AIBossAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

public:
	UBHG_AIBossAnimInstance();

protected:
	UPROPERTY(Category = "AnimType", EditAnywhere, BlueprintReadWrite)
	EAIBossMonsterAnimType	m_AnimType;

	UPROPERTY(Category = "IdleType", EditAnywhere, BlueprintReadWrite)
	bool		m_IdleBattle;

	UPROPERTY(Category = "Counter", EditAnywhere, BlueprintReadWrite)
	bool		m_CounterSuccess;


public:
	void SetAnimType(EAIBossMonsterAnimType Type);
	void SetCounterSuccess(bool Success);

public:
	const bool& GetCounterSuccess() const;
	EAIBossMonsterAnimType GetBossAnimType();

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
	void DefaultAttack1();
	void DefaultAttack2();
	void Skill1();
	void Skill2();


protected:
	UFUNCTION()
		void AnimNotify_Idle();

	UFUNCTION()
		void AnimNotify_StandIdle();

	UFUNCTION()
		void AnimNotify_RespawnEnd();

	UFUNCTION()
		void AnimNotify_DefaultAttack1Counter();

	UFUNCTION()
	void AnimNotify_DefaultAttackEnd();

	UFUNCTION()
	void AnimNotify_Attack2CounterStart();

	UFUNCTION()
	void AnimNotify_DefaultAttack2End();

	UFUNCTION()
		void AnimNotify_Skill1End();

	UFUNCTION()
		void AnimNotify_Skill1CounterAttackStart();

	UFUNCTION()
		void AnimNotify_Skill1CounterAttackEnd();

	UFUNCTION()
		void AnimNotify_GrogyEnd();

	UFUNCTION()
		void AnimNotify_Skill1Start();

	UFUNCTION()
		void AnimNotify_Skill1EffectStart();

	UFUNCTION()
		void AnimNotify_RockCreate();

	UFUNCTION()
		void AnimNotify_DecalCreate();

	UFUNCTION()
		void AnimNotify_Skill2End();

	UFUNCTION()
		void AnimNotify_CreateDefaultAttackHitBox();

	UFUNCTION()
		void AnimNotify_DestroyDefaultAttackHitBox();


	UFUNCTION()
		void AnimNotify_CreateDefaultAttack1HitBox();

	UFUNCTION()
		void AnimNotify_DestroyDefaultAttack1HitBox();

	UFUNCTION()
		void AnimNotify_CreateSkill2HitBox();

	UFUNCTION()
		void AnimNotify_DestroySkill2HitBox();
	
};
