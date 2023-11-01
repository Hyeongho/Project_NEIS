// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Grux_TargetDetect.h"
#include "../../Grux_AICharacter.h"

UBTService_Grux_TargetDetect::UBTService_Grux_TargetDetect()
{
    NodeName = TEXT("Grux_TargetDetect");

    Interval = 0.5f;
    RandomDeviation = 0.1f;
}

void UBTService_Grux_TargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    if (IsValid(Controller))
    {
        AGrux_AICharacter* Monster = Cast<AGrux_AICharacter>(Controller->GetPawn());

        if (!IsValid(Monster))
            return;

        FHitResult   HitResult;
        FCollisionQueryParams   Param;
        Param.AddIgnoredActor(Monster);

        // KKB ���� �ʿ�.
        // 2000.f�� ������ ���� ������ ���� magicnumber�� �ƴ� ����� ������ ���������� ������ �����Ѵ�.
        bool Collision = GetWorld()->SweepSingleByChannel(HitResult, Monster->GetActorLocation(), Monster->GetActorLocation(), FQuat::Identity,
            ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(4000.f), Param);

#if ENABLE_DRAW_DEBUG
        //FColor   DrawColor = Collision ? FColor::Red : FColor::Green;
        //DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), 4000.f, 20, DrawColor, false, 0.35f);
#endif

        if (Collision)
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
        else
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
    }
}
