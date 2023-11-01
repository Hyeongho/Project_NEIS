// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToShooter.h"
#include "ShooterMonster.h"
#include "../../Player/CJH/ShooterCharacter.h"

UBTTask_MoveToShooter::UBTTask_MoveToShooter()
	: Super()
{
	NodeName = TEXT("MoveToShooter");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToShooter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

	// AIPawn이 아닐 경우 정지.
	if (!IsValid(Monster))
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
		return EBTNodeResult::Failed;

	FVector Dir = Target->GetActorLocation() - Monster->GetActorLocation();
	Dir.Z = 0.0f;
	Dir.Normalize();
	Monster->SetActorRotation(FRotator(0.0f, Dir.Rotation().Yaw, 0.0f));

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_MoveToShooter::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_MoveToShooter::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

	if (!IsValid(Monster))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	AShooterCharacter* Target = Cast<AShooterCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	//FVector Dir = Monster->GetVelocity();
	//Dir.Z = 0.0f;
	//Dir.Normalize();
	//Monster->SetActorRotation(FRotator(0.0f, Dir.Rotation().Yaw, 0.0f));

	float AttackDistance = Controller->GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackDistance"));
	float DistanceToTarget = Controller->GetBlackboardComponent()->GetValueAsFloat(TEXT("DistanceToTarget"));

	if (DistanceToTarget <= AttackDistance)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	}
}

void UBTTask_MoveToShooter::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
