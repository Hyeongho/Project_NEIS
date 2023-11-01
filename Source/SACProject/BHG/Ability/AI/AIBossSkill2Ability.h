// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAbility.h"
#include "AIBossSkill2Ability.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UAIBossSkill2Ability : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UAIBossSkill2Ability();

protected:
	UPROPERTY(Category = "WarningDecal", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADecalBase>		m_WarningDecal;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>		m_Effect;

public:
	// �����Ƽ ����
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance);

	// �����Ƽ �̺�Ʈ
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0);

	// �����Ƽ ����
	virtual void EndAbility(class UAbilityComponent* OwnerComp);

	// Ÿ�̸� ������ �����Ƽ ���밡��.
	virtual void AbilityActiveOn();

	// Ability�� CoolTime�� �����ٸ�, �ش��Լ��� ���� Ÿ�̸Ӹ� ����Ѵ�. 
	virtual void AbilityCoolTimeActivated();
	
};
