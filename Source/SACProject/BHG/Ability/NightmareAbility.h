// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultAbility.h"
#include "NightmareAbility.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UNightmareAbility : public UDefaultAbility
{
	GENERATED_BODY()
	
public:
	UNightmareAbility();

protected:
	UPROPERTY(Category = "ShurikenObject", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AProjectileBase>	m_Nightmare;

	TObjectPtr<class AProjectileBase>	m_NightmareObj;

	UPROPERTY(Category = "NightmareEffect", EditAnywhere, BlueprintReadWrite);
	TSubclassOf<class ABaseEffect>		m_NightmareEffect;


	bool		m_NightmareOn;
	bool		m_SelectTarget;

public:
	// 어빌리티 실행
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance) override;

	// 어빌리티 이벤트
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0) override;

	// 어빌리티 종료
	virtual void EndAbility(class UAbilityComponent* OwnerComp) override;

	// 어빌리티 쿨타임 등록
	virtual void AbilityCoolTimeActivated() override;

	// 타이머 종료후 어빌리티 재사용가능.
	virtual void AbilityActiveOn() override;
};
