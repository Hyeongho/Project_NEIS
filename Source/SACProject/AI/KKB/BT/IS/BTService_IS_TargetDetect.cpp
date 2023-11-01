// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IS_TargetDetect.h"
#include "../../IS_AICharacter.h"

UBTService_IS_TargetDetect::UBTService_IS_TargetDetect()
{
    NodeName = TEXT("IS_TargetDetect");

    Interval = 0.5f;
    RandomDeviation = 0.1f;
}

void UBTService_IS_TargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    if (IsValid(Controller))
    {
        AIS_AICharacter* Monster = Cast<AIS_AICharacter>(Controller->GetPawn());

        if (!IsValid(Monster))
            return;

        FHitResult   HitResult;
        FCollisionQueryParams   Param;
        Param.AddIgnoredActor(Monster);

        // KKB 수정 필요.
        // 2000.f로 지정된 감지 범위는 추후 magicnumber가 아닌 저장된 값에서 가져오도록 세팅을 변경한다.
        bool Collision = GetWorld()->SweepSingleByChannel(HitResult, Monster->GetActorLocation(), Monster->GetActorLocation(), FQuat::Identity,
            ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(2000.f), Param);

#if ENABLE_DRAW_DEBUG
        //FColor   DrawColor = Collision ? FColor::Red : FColor::Green;
        //DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), 2000.f, 20, DrawColor, false, 0.35f);
#endif

        if (Collision)
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
        else
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
    }
}
