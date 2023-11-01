// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AuroraMoveInteraction.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTTask_AuroraMoveInteraction : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_AuroraMoveInteraction();

protected:
	// 이 Task가 동작될때 호출된다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	// 작업을 중단할 때 들어온다.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	// 매 프레임마다 동작한다.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	// Task가 종료될때 동작한다.
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
};
