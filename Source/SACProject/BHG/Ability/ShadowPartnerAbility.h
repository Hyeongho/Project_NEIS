// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultAbility.h"
#include "ShadowPartnerAbility.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class SACPROJECT_API UShadowPartnerAbility : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UShadowPartnerAbility();

protected:
	UPROPERTY(Category = "ShadowPlayer", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class APlayerCharacter>	m_Shadow;

public:
	// �����Ƽ ����
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance);

	// �����Ƽ �̺�Ʈ
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0);

	// Ÿ�̸� ������ �����Ƽ ���밡��.
	virtual void AbilityActiveOn();

	// Ability�� CoolTime�� �����ٸ�, �ش��Լ��� ���� Ÿ�̸Ӹ� ����Ѵ�. 
	virtual void AbilityCoolTimeActivated();
	
};
