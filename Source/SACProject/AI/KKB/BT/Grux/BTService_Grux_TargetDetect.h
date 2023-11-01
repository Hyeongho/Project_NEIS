// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Grux_TargetDetect.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTService_Grux_TargetDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Grux_TargetDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
