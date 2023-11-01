// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IS_AttackCheck.generated.h"

UENUM(BlueprintType)
enum class EISAttackCheck : uint8
{
	Attack,
	Interaction
};

UCLASS()
class SACPROJECT_API UBTDecorator_IS_AttackCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IS_AttackCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EISAttackCheck m_CheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
