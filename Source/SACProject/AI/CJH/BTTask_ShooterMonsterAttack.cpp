// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShooterMonsterAttack.h"
#include "ShooterMonster.h"

UBTTask_ShooterMonsterAttack::UBTTask_ShooterMonsterAttack()
	: Super()
{
	NodeName = TEXT("ShooterMonsterAttack");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_ShooterMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

	// AIPawn이 아닐 경우 정지.
	if (!IsValid(Monster))
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if(!IsValid(Target))
		return EBTNodeResult::Failed;

	FVector Dir = Target->GetActorLocation() - Monster->GetActorLocation();
	Dir.Z = 0.0f;
	Dir.Normalize();
	Monster->SetActorRotation(FRotator(0.0f, Dir.Rotation().Yaw, 0.0f));

	Monster->PlayAttackMontage(Monster->GetAttackSectionName());

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_ShooterMonsterAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_ShooterMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

	if (!IsValid(Monster))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (Monster->GetMesh()->GetAnimInstance()->Montage_IsPlaying(Monster->GetAttackMontage()))
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	else
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_ShooterMonsterAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
