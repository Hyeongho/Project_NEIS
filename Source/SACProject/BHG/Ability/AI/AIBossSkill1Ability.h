// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAbility.h"
#include "AIBossSkill1Ability.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UAIBossSkill1Ability : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UAIBossSkill1Ability();

protected:
	UPROPERTY(Category = "RockSpawner", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADefaultSpawnObject>	BossRockSpawnObj;

	UPROPERTY(Category = "Skill1Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>		Skill1Effect;
	

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
