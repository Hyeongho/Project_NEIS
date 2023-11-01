// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AIBossDefaultAttack1.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTTask_AIBossDefaultAttack1 : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AIBossDefaultAttack1();

protected:
	bool BossAttack;
	float LimitTime;

protected:
	// 이 Task가 동작될때 호출된다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

	// 작업을 중단할 때 들어온다.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

	// 매 프레임마다 동작한다.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds) override;

	// Task가 종료될때 동작한다.
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
};
