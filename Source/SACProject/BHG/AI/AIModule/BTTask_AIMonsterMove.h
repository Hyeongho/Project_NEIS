// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AIMonsterMove.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTTask_AIMonsterMove : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AIMonsterMove();



protected:
	// �� Task�� ���۵ɶ� ȣ��ȴ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

	// �۾��� �ߴ��� �� ���´�.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

	// �� �����Ӹ��� �����Ѵ�.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;

	// Task�� ����ɶ� �����Ѵ�.
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
};
