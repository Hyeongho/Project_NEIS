// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Grux_IsBerserk.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_Grux_IsBerserk : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_Grux_IsBerserk();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
