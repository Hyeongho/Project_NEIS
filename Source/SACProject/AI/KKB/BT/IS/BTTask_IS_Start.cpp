// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IS_Start.h"
#include "../../IS_AICharacter.h"
#include "../../../DefaultAIAnimInstance.h"

UBTTask_IS_Start::UBTTask_IS_Start()
{
	NodeName = TEXT("IS_Start");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_IS_Start::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AIS_AICharacter* ISCharacter = Cast<AIS_AICharacter>(Controller->GetCharacter());

	if (IsValid(ISCharacter)) {
		// Start Anim ½ÇÇà
		ISCharacter->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Start);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_IS_Start::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_IS_Start::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	return;

	//AAIController* Controller = OwnerComp.GetAIOwner();

	//AIS_AICharacter* ISCharacter = Cast<AIS_AICharacter>(Controller->GetCharacter());

	//if (IsValid(ISCharacter)) {
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	//	ISCharacter->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

	//	Controller->StopMovement();
	//}
}

void UBTTask_IS_Start::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
