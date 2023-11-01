// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIMonsterMove.h"
#include "../BHG_AIController.h"
#include "../../Animation/BHG_AIAnimInstance.h"
#include "../AI_Monster.h"

UBTTask_AIMonsterMove::UBTTask_AIMonsterMove()
    : Super()
{
    NodeName = TEXT("Move");
    bNotifyTick = true;

    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AIMonsterMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
    

    UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

    Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Run);

    return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AIMonsterMove::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::AbortTask(OwnerComp, NodeMemory);

    return EBTNodeResult::Type();
}

void UBTTask_AIMonsterMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

    if (!IsValid(AIMonster))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

        Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

        return;
    }

    AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (!IsValid(Target))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

        Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

        return;
    }

    FVector Dir = AIMonster->GetMovementComponent()->Velocity; 

    FRotator CurrentRotation = AIMonster->GetActorRotation();

    UBHG_AIAnimInstance* MonsterAnim = Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance());

    if (MonsterAnim->GetMonsterAnimType() == EAIMonsterAnimType::Die)
        return;

    if (Dir.X != 0 || Dir.Y != 0.f && MonsterAnim->GetMonsterAnimType() != EAIMonsterAnimType::Die)
    {

        AActor* TargetPlayer = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

        FRotator DesiredRotation = (TargetPlayer->GetActorLocation() - AIMonster->GetActorLocation()).Rotation();
        FRotator DeltaRotation = DesiredRotation - CurrentRotation;

        float InterpSpeed = 5.f; // 조절 가능한 값
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaSeconds, InterpSpeed);

        AIMonster->SetActorRotation(NewRotation);

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

    if (Distance <= 100.f)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

       // Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIMonsterAnimType::Idle);

        Controller->StopMovement();
    }

}

void UBTTask_AIMonsterMove::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
}
