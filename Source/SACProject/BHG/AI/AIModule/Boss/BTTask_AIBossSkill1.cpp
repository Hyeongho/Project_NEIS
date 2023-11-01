// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIBossSkill1.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"

UBTTask_AIBossSkill1::UBTTask_AIBossSkill1() :
	Super()
{
	NodeName = TEXT("BossSkill1");
	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_AIBossSkill1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    if(!AIBossMonster->GetBossDie())
    AIBossMonster->BossSkill1();

    return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AIBossSkill1::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_AIBossSkill1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

    FVector	AILoc = AIBossMonster->GetActorLocation();
    FVector	TargetLoc = Target->GetActorLocation();

    FVector TargetAxis = TargetLoc - AILoc;

    AILoc.Z -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    TargetLoc.Z -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    float Distance = FVector::Distance(AILoc, TargetLoc);

    // 거리에서 각 물체들의 캡슐 반경을 빼준다.
    Distance -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();

    // Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
    UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

    if (IsValid(Capsule))
    {
        Distance -= Capsule->GetScaledCapsuleRadius();
    }

    if (Distance > 300.f)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }

    else
    {
        FVector Dir = TargetLoc - AILoc;
        Dir.Z = 0.0;

        Dir.Normalize();

        UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance());

        if (!BossAnim->GetCounterSuccess() && AIBossMonster->GetBossAbilityEnable())
            AIBossMonster->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

        if (AIBossMonster->GetBossAbilityEnable())
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

            Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), false);
        }
    }
}

void UBTTask_AIBossSkill1::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
