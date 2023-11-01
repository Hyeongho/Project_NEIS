// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IS_Alive.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_IS_Alive : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IS_Alive();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
