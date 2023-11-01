// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerAnimInstance.h"
#include "TerraAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ETerraAnimType : uint8
{
	Default,
	Jump,
	Fall,
	Attack,
	GuradIntro, 
	Gurad, 
	GuradEnd, 
	Skill, 
	Death,
	Teleport
};

UENUM(BlueprintType)
enum class ETerraSkill : uint8
{
	Q, 
	E, 
	R
};

UCLASS()
class SACPROJECT_API UTerraAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UTerraAnimInstance();

protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ETerraAnimType m_AnimType;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_AttackMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> m_GuradIntroMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> m_GuradEndMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_SkillMontage;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool m_IsGurad;

	int32 m_AttackIndex;
	bool m_AttackEnable;

public:
	void ChangeAnim(ETerraAnimType AnimType)
	{
		m_AnimType = AnimType;
	}

	ETerraAnimType GetAnimType() const
	{
		return m_AnimType;
	}

public:
	virtual void Attack();

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
	void GuradIntro();
	void Skill(int Index);

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_GuradStart();
	
	UFUNCTION()
	void AnimNotify_PrintEffect();

	UFUNCTION()
	void AnimNotify_SkillEnd();
};
