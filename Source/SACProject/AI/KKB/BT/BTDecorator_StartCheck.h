// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_StartCheck.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_StartCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_StartCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
