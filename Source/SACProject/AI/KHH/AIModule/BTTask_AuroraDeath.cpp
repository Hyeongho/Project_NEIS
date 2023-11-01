// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AuroraDeath.h"
#include "../AuroraAICharacter.h"
#include "../AuroraAIAnimInstance.h"
#include "../../AIState.h"

UBTTask_AuroraDeath::UBTTask_AuroraDeath()
{
	NodeName = TEXT("AuroraDeath");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AuroraDeath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	int32 HP = Controller->GetBlackboardComponent()->GetValueAsInt(TEXT("HP"));

	AAuroraAICharacter* Auroar = Cast<AAuroraAICharacter>(Controller->GetPawn());

	if (!IsValid(Auroar))
	{
		return EBTNodeResult::Failed;
	}

	if (HP > 0)
	{
		Controller->StopMovement();

		Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Death);

	//Auroar->Death();

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AuroraDeath::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AuroraDeath::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	int32 HP = Controller->GetBlackboardComponent()->GetValueAsInt(TEXT("HP"));
}

void UBTTask_AuroraDeath::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
