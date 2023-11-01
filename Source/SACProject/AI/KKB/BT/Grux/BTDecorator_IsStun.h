// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsStun.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_IsStun : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsStun();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
