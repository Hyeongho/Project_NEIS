// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerAnimInstance.h"
#include "Kwang_AnimInstance.generated.h"

UENUM(BlueprintType)
enum class EKwangAnimType : uint8 {
	Default,
	Start,
	Idle,
	Move,
	Attack,
	Skill,
	Death
};

enum class EKwangSkill {
	Skill1_Started,
	Skill1_Charging,
	Skill1_Released,
	Skill2_Started,
	Skill3_Started
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UKwang_AnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
public :
	UKwang_AnimInstance();

protected:
	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AKwang_PlayerCharacter>	m_Player;

	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(Category = "Animation", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EKwangAnimType m_AnimType;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_AttackMontage;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_AttackMontage_Enhance;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_SkillMontage;

	int32 m_AttackIndex;
	bool m_AttackEnable;
	bool m_Charging;

public:
	void ChangeAnim(EKwangAnimType AnimType)
	{
		m_AnimType = AnimType;
	}

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
	void Attack();
	void Dash();
	void Skill1();
	void Skill1Canceled();
	void Skill1Release();
	void Skill2();
	void Skill3();

private:
	void ActionEnable();
	void ActionDisable();

public: // Attack Notify
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_Attack2();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public: // Skill Notify
	UFUNCTION()
	void AnimNotify_ShootEnable();

	UFUNCTION()
	void AnimNotify_FirstCharge();

	UFUNCTION()
	void AnimNotify_SecondCharge();

	UFUNCTION()
	void AnimNotify_ChargeEnd();

	UFUNCTION()
	void AnimNotify_ChargeShoot();

	UFUNCTION()
	void AnimNotify_Skill2Ability();

	UFUNCTION()
	void AnimNotify_Skill2Ability2();

	UFUNCTION()
	void AnimNotify_Skill3Ability();

	UFUNCTION()
	void AnimNotify_AbilityStart();

	UFUNCTION()
	void AnimNotify_AbilityEnd();


};
