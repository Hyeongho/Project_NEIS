// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Grux_BaseAttack.h"
#include "../../Grux_AIController.h"
#include "../../Grux_AICharacter.h"

UBTTask_Grux_BaseAttack::UBTTask_Grux_BaseAttack()
{
	NodeName = TEXT("Grux_BaseAttack");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Grux_BaseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());

	if (IsValid(GruxCharacter)) {
		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target)) {
			GruxCharacter->Attack();

			return EBTNodeResult::Succeeded;
		}

		// Target이 없을 경우 행동을 중지하고 Idle 상태로 되돌림
		Controller->StopMovement();
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Grux_BaseAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Grux_BaseAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Grux_BaseAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
