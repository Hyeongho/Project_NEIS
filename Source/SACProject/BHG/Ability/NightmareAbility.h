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
	// �����Ƽ ����
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance) override;

	// �����Ƽ �̺�Ʈ
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0) override;

	// �����Ƽ ����
	virtual void EndAbility(class UAbilityComponent* OwnerComp) override;

	// �����Ƽ ��Ÿ�� ���
	virtual void AbilityCoolTimeActivated() override;

	// Ÿ�̸� ������ �����Ƽ ���밡��.
	virtual void AbilityActiveOn() override;
};
