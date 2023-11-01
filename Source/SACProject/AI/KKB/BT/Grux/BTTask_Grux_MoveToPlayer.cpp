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
		// Idle ������ ������ ������ �����ϰ� ����.
		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target)) {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

			Cast<UGrux_AIAnimInst>(GruxCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Walk);

			return EBTNodeResult::InProgress;
		}

		// Target�� ���� ��� �ൿ�� �����ϰ� Idle ���·� �ǵ���
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

	// Ÿ�ٰ� �ڽ��� valid üũ��, �����ϸ� �ൿ ����
	if (!IsValid(GruxCharacter) || !IsValid(Target)) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();
		//Cast<UIS_AIAnimInst>(ISCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	// Ÿ���� �ٶ󺸰�, �Ÿ��� �ָ� �̵��ϵ��� ����
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
