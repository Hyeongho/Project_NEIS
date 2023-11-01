// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIBossDefaultAttack2.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"

UBTTask_AIBossDefaultAttack2::UBTTask_AIBossDefaultAttack2() :
	Super()
{
	NodeName = TEXT("BossDefaultAttack2");
	bNotifyTick = true;

	bNotifyTaskFinished = true;

    LimitTime = 0.f;
}

EBTNodeResult::Type UBTTask_AIBossDefaultAttack2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    BossAttack = false;

    Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), true);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AIBossDefaultAttack2::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_AIBossDefaultAttack2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
    /*    FVector Dir = TargetLoc - AILoc;
        Dir.Z = 0.0;

        Dir.Normalize();

     

        if (!BossAnim->GetCounterSuccess() && AIBossMonster->GetBossAbilityEnable())
            AIBossMonster->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

        if (AIBossMonster->GetBossAbilityEnable())
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

            Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), false);
        }*/

        FRotator CurrentRotation = AIBossMonster->GetActorRotation();

        UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance());

        bool Test1 = BossAnim->GetCounterSuccess();
        bool Test2 = AIBossMonster->GetBossAbilityEnable();
        bool Test3 = BossAttack;


        //공격전에 플레이어방향으로 회전시킨다. 
        if (!BossAnim->GetCounterSuccess() && AIBossMonster->GetBossAbilityEnable() && !BossAttack)
        {
            //AIBossMonster->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

            AActor* TargetPlayer = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

            FRotator DesiredRotation = (TargetPlayer->GetActorLocation() - AIBossMonster->GetActorLocation()).Rotation();
            FRotator DeltaRotation = DesiredRotation - CurrentRotation;

            float InterpSpeed = 5.f; // 조절 가능한 값
            FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaSeconds, InterpSpeed);

            AIBossMonster->SetActorRotation(NewRotation);

            FVector MonLoc = AIBossMonster->GetActorLocation();
            FVector TarLoc = TargetPlayer->GetActorLocation();

            FVector DirectionToPlayer = (TarLoc - MonLoc).GetSafeNormal();

            //만약 플레이어가 앞에 있다면 ?
            float DotValue = FVector::DotProduct(DirectionToPlayer, AIBossMonster->GetActorForwardVector());

            if (DotValue > 0.9f)
            {
                ////공격을 진행한다.
                //Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), true);

                AIBossMonster->BossDefaultAttack2();

                BossAttack = true;

                Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), false);

                LimitTime = 0.f;

                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
              
            }
        }  

    
    }
}

void UBTTask_AIBossDefaultAttack2::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
    
}
