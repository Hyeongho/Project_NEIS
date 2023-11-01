// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../DefaultAbility.h"
#include "AIBossDefaultAttack2Ability.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UAIBossDefaultAttack2Ability : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UAIBossDefaultAttack2Ability();

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
