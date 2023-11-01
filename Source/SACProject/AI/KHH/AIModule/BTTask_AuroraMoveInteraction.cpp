// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AuroraMoveInteraction.h"
#include "../AuroraAICharacter.h"
#include "../AuroraAIAnimInstance.h"
#include "../../AIState.h"

UBTTask_AuroraMoveInteraction::UBTTask_AuroraMoveInteraction()
{
	NodeName = TEXT("AuroraMoveInteraction");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AuroraMoveInteraction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	int32 HP = Controller->GetBlackboardComponent()->GetValueAsInt(TEXT("HP"));

	if (HP <= 0)
	{
		Controller->StopMovement();

		return EBTNodeResult::Failed;
	}

	AAuroraAICharacter* Auroar = Cast<AAuroraAICharacter>(Controller->GetPawn());

	if (!IsValid(Auroar))
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		Controller->StopMovement();

		Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		//LOG(TEXT("Idle"));

		return EBTNodeResult::Failed;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	//LOG(TEXT("%S %S"), AICharacter->GetName(), Controller->GetName());

	Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Run);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AuroraMoveInteraction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AuroraMoveInteraction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	int32 HP = Controller->GetBlackboardComponent()->GetValueAsInt(TEXT("HP"));

	if (HP <= 0)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		return;
	}

	AAuroraAICharacter* Auroar = Cast<AAuroraAICharacter>(Controller->GetPawn());

	if (!IsValid(Auroar))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		//LOG(TEXT("Idle"));

		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		Auroar->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		//LOG(TEXT("Idle"));

		return;
	}

	FVector Dir = Auroar->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;

	Dir.Normalize();

	Auroar->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

	FVector	AILoc = Auroar->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z -= Auroar->GetHalfHeight();
	TargetLoc.Z -= Auroar->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	Distance -= Auroar->GetCapsuleRadius();

	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	if (Distance <= Auroar->GetAIState()->GetAttackDistance())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();
	}
}

void UBTTask_AuroraMoveInteraction::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
