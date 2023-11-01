// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../Player/PlayerAnimInstance.h"
#include "BHG_PlayerAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EBHGPlayerAninType : uint8
{
	Idle,
	Nightmare,
	Hit,
	Die,
};

UCLASS()
class SACPROJECT_API UBHG_PlayerAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

public:
	UBHG_PlayerAnimInstance();

protected:
	UPROPERTY(Category = "AnimType", EditAnywhere, BlueprintReadWrite)
	EBHGPlayerAninType	m_PlayerAnimType;

	UPROPERTY(Category = "Data", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		m_ForwardSpeed;

	UPROPERTY(Category = "Data", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		m_RightSpeed;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> mAttackMontage;


	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> mShurikenMontage;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> mNightmareMontage;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> mCounterMontage;

	UPROPERTY(Category = "HitEnable", VisibleAnywhere, BlueprintReadOnly)
	bool mHitEnable;

	bool mAttackEnable;
	bool mMoveEnable;
	int32	mAttackIndex;



public:
	void SetAnimType(EBHGPlayerAninType Type);
	void SetForwardSpeed(float Speed) { m_ForwardSpeed = Speed; }
	void SetRightSpeed(float Speed) { m_RightSpeed = Speed; }
	void SetHitEnable(bool Enable);

public:
	const float& GetForwardSpeed() const { return m_ForwardSpeed; }
	const float& GetRightSpeed() const { return m_RightSpeed; }
	const bool& GetAttackEnable() const { return mAttackEnable; }

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
	virtual void DefaultAttack();
	virtual void ShurikenAttack();
	virtual void CounterAttack();
	void NightmareAttack();


public:
	UFUNCTION()
		void AnimNotify_NightmareEnd();

	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_Attack2();

	UFUNCTION()
		void AnimNotify_ShurikenAttack();

	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_NightmareStart();

	UFUNCTION()
		void AnimNotify_NightmareAttack();

	UFUNCTION()
		void AnimNotify_NightmareAttackEnd();

	UFUNCTION()
		void AnimNotify_CounterAttack();

	UFUNCTION()
		void AnimNotify_CounterAttackEnd();

	UFUNCTION()
		void AnimNotify_AttackHitBox();

	UFUNCTION()
		void AnimNotify_AttackHitBoxEnd();

	UFUNCTION()
		void AnimNotify_PlayerHitEnd();
	
};
