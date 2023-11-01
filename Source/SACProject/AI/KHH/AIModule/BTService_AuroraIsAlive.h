// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AuroraIsAlive.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTService_AuroraIsAlive : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_AuroraIsAlive();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
