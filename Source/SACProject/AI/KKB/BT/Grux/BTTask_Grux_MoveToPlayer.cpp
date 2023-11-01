// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Grux_MoveToPlayer.h"
#include "../../Grux_AIController.h"
#include "../../Grux_AICharacter.h"
#include "../../Grux_AIAnimInst.h"
#include "../../../AIState.h"

UBTTask_Grux_MoveToPlayer::UBTTask_Grux_MoveToPlayer()
{
	NodeName = TEXT("Grux_MoveToPlayer");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Grux_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());

	if (IsValid(GruxCharacter)) {
		// Idle 상태일 때에만 동작을 가능하게 설정.
		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target)) {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

			Cast<UGrux_AIAnimInst>(GruxCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Walk);

			return EBTNodeResult::InProgress;
		}

		// Target이 없을 경우 행동을 중지하고 Idle 상태로 되돌림
		Controller->StopMovement();

		//Cast<UIS_AIAnimInst>(ISCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Idle);
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Grux_MoveToPlayer::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Grux_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 타겟과 자신을 valid 체크해, 실패하면 행동 중지
	if (!IsValid(GruxCharacter) || !IsValid(Target)) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();
		//Cast<UIS_AIAnimInst>(ISCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	// 타겟을 바라보고, 거리가 멀면 이동하도록 설정
	FVector	AILoc = GruxCharacter->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z = 0.f;
	TargetLoc.Z = 0.f;

	FVector Dir = (TargetLoc - AILoc).GetSafeNormal();
	GruxCharacter->SetActorRotation(Dir.Rotation());


	float Distance = FVector::Distance(AILoc, TargetLoc);

	float AtkDist = GruxCharacter->GetAIState()->GetAttackDistance();

	if (Distance <= AtkDist) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();
	}
}

void UBTTask_Grux_MoveToPlayer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
