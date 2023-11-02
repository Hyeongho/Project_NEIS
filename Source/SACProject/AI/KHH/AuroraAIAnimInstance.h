// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIAnimInstance.h"
#include "../../Component/KKB/CoolDownComponent.h"
#include "AuroraAIAnimInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAuroraSkill
{
	GENERATED_BODY()

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> SkillMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxCoolTime = 0;

	float CurCoolTime = 0;

	bool IsCool = true;
};

UCLASS()
class SACPROJECT_API UAuroraAIAnimInstance : public UDefaultAIAnimInstance
{
	GENERATED_BODY()

public:
	UAuroraAIAnimInstance();
	
protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_AttackMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_SkillMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> m_StartMontage;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FAuroraSkill> m_Skill;

	int32 m_AttackIndex;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_AttackEnable;

private:
	void PlayStart();

public:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

	virtual void NativePostEvaluateAnimation();

	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

public:
	void Skill(int Index);
	void Attack();

public:
	TArray<FAuroraSkill> GetSkillArray() const
	{
		return m_Skill;
	}

	TObjectPtr<UAnimMontage> GetSkill(int index) const
	{
		return m_Skill[index].SkillMontage;
	}

	int GetSkillCurCoolTime(int index) const
	{
		return m_Skill[index].CurCoolTime;
	}

	int GetSkillCurMaxCoolTime(int index) const
	{
		return m_Skill[index].MaxCoolTime;
	}

	void SetAttackIndex(int32 index)
	{
		m_AttackIndex = index;
	}

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_StartEnd();

	UFUNCTION()
	void AnimNotify_StartEffect();

	UFUNCTION()
	void AnimNotify_AuroraDash();

	UFUNCTION()
	void AnimNotify_DassStart();

	UFUNCTION()
	void AnimNotify_DassEnd();

	UFUNCTION()
	void AnimNotify_AuroraFreeze();

	UFUNCTION()
	void AnimNotify_FreezeEnd();

	UFUNCTION()
	void AnimNotify_AuroraUltimate();

	UFUNCTION()
	void AnimNotify_AuroraDeath();
};
