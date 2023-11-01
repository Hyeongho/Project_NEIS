// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIMonsterAttack.h"
#include "../BHG_AIController.h"
#include "../../Animation/BHG_AIAnimInstance.h"
#include "../AI_Monster.h"

UBTTask_AIMonsterAttack::UBTTask_AIMonsterAttack()
    : Super()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AIMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

	if (!IsValid(AIMonster))
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		Controller->StopMovement();

		Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

    if(!Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->GetHitEnable())
	    AIMonster->DefaultAttack();

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AIMonsterAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AIMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

    if (!IsValid(AIMonster))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

        //Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

        return;
    }

    AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (!IsValid(Target))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

       // Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

        return;
    }

    FVector	AILoc = AIMonster->GetActorLocation();
    FVector	TargetLoc = Target->GetActorLocation();

    FVector TargetAxis = TargetLoc - AILoc;

    AILoc.Z -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    TargetLoc.Z -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    float Distance = FVector::Distance(AILoc, TargetLoc);

    // 거리에서 각 물체들의 캡슐 반경을 빼준다.
    Distance -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();

    // Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
    UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

    if (IsValid(Capsule))
    {
        Distance -= Capsule->GetScaledCapsuleRadius();
    }

    if (Distance > 100.f)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }

    else
    {
        FVector Dir = TargetLoc - AILoc;
        Dir.Z = 0.0;

        Dir.Normalize();

        AIMonster->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

void UBTTask_AIMonsterAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

  
}
