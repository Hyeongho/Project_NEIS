// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BT_Service_AIBossTargetDetect.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBT_Service_AIBossTargetDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBT_Service_AIBossTargetDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
		float DeltaSeconds) override;
	
};
