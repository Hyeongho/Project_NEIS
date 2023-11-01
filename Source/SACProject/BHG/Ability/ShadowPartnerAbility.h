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
	// 어빌리티 실행
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance);

	// 어빌리티 이벤트
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0);

	// 타이머 종료후 어빌리티 재사용가능.
	virtual void AbilityActiveOn();

	// Ability가 CoolTime을 가진다면, 해당함수를 통해 타이머를 등록한다. 
	virtual void AbilityCoolTimeActivated();
	
};
