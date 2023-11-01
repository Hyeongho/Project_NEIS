// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "DefaultAbility.generated.h"

/**
 Base Class 이므로 핵심 기능은 상속받아서 하위클래스에서 구현할것. 
 */
UCLASS(BlueprintType, Blueprintable, config = Engine)
class SACPROJECT_API UDefaultAbility : public UObject
{
	GENERATED_BODY()

public:
	UDefaultAbility();

protected:
	//어빌리티 이름

	UPROPERTY(Category = "AbilityName", EditAnywhere, BlueprintReadWrite);
	FName		m_AbilityName;

	//어빌리티의 쿨타임

	UPROPERTY(Category = "AbilityCoolTime", EditAnywhere, BlueprintReadWrite);
	float		m_AbilityCoolTime;

	//어빌리티가 생성할 충돌체

	UPROPERTY(Category = "AbilitHitBox", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AHitBoxObject>		m_AbilityHitBox;

	//해당 어빌리티가 카운터공격이 가능한 어빌리티인지 ?
	UPROPERTY(Category = "CounterEnable", EditAnywhere, BlueprintReadWrite)
	bool		m_CounterAbility;

	class AHitBoxObject* m_AbilityHitBoxObj;

	bool		m_AbilityActive;
	FTimerHandle m_AbilityTimerHandle;
	bool		m_AbilityTimerActive;

public:
	const FName& GetAbilityName() const;
	float GetAbilityCoolTime();
	float GetOriginCoolTime();
	const bool& GetAbilityActive() const;
	const bool& GetAbilityLockMove() const;
	const bool& GetMoveEnable() const;



public:
	// 어빌리티 실행
	virtual void ActivatedAbility(class UAbilityComponent* OwnerComp, class UAnimInstance* AnimInstance);

	// 어빌리티 이벤트
	virtual void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0);

	// 어빌리티 종료
	virtual void EndAbility(class UAbilityComponent* OwnerComp);

	// 타이머 종료후 어빌리티 재사용가능.
	virtual void AbilityActiveOn();	

	// Ability가 CoolTime을 가진다면, 해당함수를 통해 타이머를 등록한다. 
	virtual void AbilityCoolTimeActivated();
};
