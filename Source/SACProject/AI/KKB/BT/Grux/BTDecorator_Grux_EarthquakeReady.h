// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Grux_EarthquakeReady.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_Grux_EarthquakeReady : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_Grux_EarthquakeReady();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
