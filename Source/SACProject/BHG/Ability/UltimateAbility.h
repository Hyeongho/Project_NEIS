// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DefaultAbility.h"
#include "UltimateAbility.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UUltimateAbility : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UUltimateAbility();

protected:
	UPROPERTY(Category = "ShadowSpanwer", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADefaultSpawnObject>		m_ShadowSpawner;

public:
	// �����Ƽ ����
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance);

	// �����Ƽ �̺�Ʈ
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner,class APawn* Target, int32 Value = 0);

	// Ÿ�̸� ������ �����Ƽ ���밡��.
	virtual void AbilityActiveOn();

	// Ability�� CoolTime�� �����ٸ�, �ش��Լ��� ���� Ÿ�̸Ӹ� ����Ѵ�. 
	virtual void AbilityCoolTimeActivated();	
};
