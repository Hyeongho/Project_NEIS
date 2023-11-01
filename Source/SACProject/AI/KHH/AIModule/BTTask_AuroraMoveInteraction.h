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
	// �� Task�� ���۵ɶ� ȣ��ȴ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	// �۾��� �ߴ��� �� ���´�.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	// �� �����Ӹ��� �����Ѵ�.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	// Task�� ����ɶ� �����Ѵ�.
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
};
