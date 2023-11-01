// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectShooter.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTService_DetectShooter : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_DetectShooter();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
