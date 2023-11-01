// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Grux_Earthquake.h"
#include "../../Grux_AIController.h"
#include "../../Grux_AICharacter.h"

UBTTask_Grux_Earthquake::UBTTask_Grux_Earthquake()
{
	NodeName = TEXT("Grux_Earthquake");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Grux_Earthquake::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());

	if (IsValid(GruxCharacter)) {
		// 포효 스킬을 사용하고, 어스퀘이크를 동작시킨다.
		GruxCharacter->Skill3_Earthquake();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Grux_Earthquake::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Grux_Earthquake::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Grux_Earthquake::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
