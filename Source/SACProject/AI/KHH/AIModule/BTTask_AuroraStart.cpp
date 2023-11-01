// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AuroraStart.h"
#include "../AuroraAICharacter.h"
#include "../AuroraAIAnimInstance.h"

UBTTask_AuroraStart::UBTTask_AuroraStart()
{
	NodeName = TEXT("AuroraMoveInteraction");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AuroraStart::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (!IsValid(Aurora))
	{
		return EBTNodeResult::Failed;
	}

	Aurora->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Start);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AuroraStart::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AuroraStart::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (!IsValid(Aurora))
	{
		return;
	}

	if (Aurora->GetStartEnd())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Aurora->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		Controller->StopMovement();

		return;
	}
}

void UBTTask_AuroraStart::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
