// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DefaultAbility.h"
#include "DefaultAttackAbility.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class SACPROJECT_API UDefaultAttackAbility : public UDefaultAbility
{
	GENERATED_BODY()

public:
	UDefaultAttackAbility();


public:
	// 어빌리티 실행
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance) override;

	// 어빌리티 이벤트
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0) override;

	virtual void AbilityCoolTimeActivated() override;

	// 타이머 종료후 어빌리티 재사용가능.
	virtual void AbilityActiveOn() override;
	
};
