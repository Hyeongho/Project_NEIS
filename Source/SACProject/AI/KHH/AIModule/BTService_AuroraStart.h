// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AuroraStart.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTService_AuroraStart : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_AuroraStart();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
