// Fill out your copyright notice in the Description page of Project Settings.



#include "BTTask_AIBossMove.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"

UBTTask_AIBossMove::UBTTask_AIBossMove()
{
	NodeName = TEXT("BossMove");
	bNotifyTick = true;

	bNotifyTaskFinished = true;

    BossMoveOn = false;
}

EBTNodeResult::Type UBTTask_AIBossMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();

    AAI_BossMonster* AIBossMonster = Cast<AAI_BossMonster>(Controller->GetPawn());

    if (!IsValid(AIBossMonster))
        return EBTNodeResult::Failed;

    AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (!IsValid(Target))
    {
        Controller->StopMovement();

        Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Idle);

        return EBTNodeResult::Failed;
    }

    if (AIBossMonster->GetBossAbilityEnable())
    {
        UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

        Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Run);

        BossMoveOn = true;
    }

    if (AIBossMonster->GetBossDie())
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);


    return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AIBossMove::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AIBossMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    AAI_BossMonster* AIBossMonster = Cast<AAI_BossMonster>(Controller->GetPawn());

    if (AIBossMonster->GetBossDie())
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    if (!IsValid(AIBossMonster))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

        Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Idle);

        return;
    }

    AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (!IsValid(Target))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

        Controller->StopMovement();

        Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Idle);

        return;
    }


    if (!BossMoveOn)
    {
        if (AIBossMonster->GetBossAbilityEnable() && !AIBossMonster->GetBossDie())
        {
            UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

            Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Run);

            BossMoveOn = true;
        }
    }


    FVector Dir = AIBossMonster->GetMovementComponent()->Velocity;

    FRotator CurrentRotation = AIBossMonster->GetActorRotation();

    if (Dir.X != 0 || Dir.Y != 0.f)
    {      

        AActor* TargetPlayer = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

        FRotator DesiredRotation = (TargetPlayer->GetActorLocation() - AIBossMonster->GetActorLocation()).Rotation();
        FRotator DeltaRotation = DesiredRotation - CurrentRotation;

        float InterpSpeed = 5.f; // 조절 가능한 값
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaSeconds, InterpSpeed);

        AIBossMonster->SetActorRotation(NewRotation);

    }
    
    FVector	AILoc = AIBossMonster->GetActorLocation();
    FVector	TargetLoc = Target->GetActorLocation();

    FVector TargetAxis = (TargetLoc - AILoc).GetSafeNormal();

    AILoc.Z -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    TargetLoc.Z -= Cast<ACharacter>(Target)->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    float Distance = FVector::Distance(AILoc, TargetLoc);

    // 거리에서 각 물체들의 캡슐 반경을 빼준다.
    Distance -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();

    // Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
    UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

    if (IsValid(Capsule))
    {
        Distance -= Capsule->GetScaledCapsuleRadius();
    }

    if (Distance <= 250.f)
    { 

        Controller->StopMovement();     

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

        Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance())->SetAnimType(EAIBossMonsterAnimType::Idle);

        BossMoveOn = false;
    }
}

void UBTTask_AIBossMove::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
