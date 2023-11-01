// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Grux_StampedeCooling.h"
#include "../../Grux_AIController.h"
#include "../../Grux_AICharacter.h"
#include "../../../AIState.h"

UBTTask_Grux_StampedeCooling::UBTTask_Grux_StampedeCooling()
{
	NodeName = TEXT("Grux_StampedeCooling");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Grux_StampedeCooling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());

	if (IsValid(GruxCharacter)) {
		GruxCharacter->StartStampedeCooldown();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Grux_StampedeCooling::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Grux_StampedeCooling::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Grux_StampedeCooling::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
