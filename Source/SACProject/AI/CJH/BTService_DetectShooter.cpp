// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectShooter.h"
#include "ShooterMonster.h"
#include "../AIState.h"

UBTService_DetectShooter::UBTService_DetectShooter()
	: Super()
{
	NodeName = TEXT("DetectShooter");

	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_DetectShooter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    if (IsValid(Controller))
    {
        AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

        if (!IsValid(Monster))
            return;

        FHitResult   HitResult;
        FCollisionQueryParams   Param;
        Param.AddIgnoredActor(Monster);

        const float DetectRange = Controller->GetBlackboardComponent()->GetValueAsFloat(TEXT("InteractionDistance"));

        bool Collision = GetWorld()->SweepSingleByChannel(HitResult, Monster->GetActorLocation(), Monster->GetActorLocation(), FQuat::Identity,
            ECollisionChannel::ECC_GameTraceChannel9, FCollisionShape::MakeSphere(DetectRange), Param);

#if ENABLE_DRAW_DEBUG

        //FColor   DrawColor = Collision ? FColor::Red : FColor::Green;
        //DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), DetectRange, 20, DrawColor, false, 0.35f);

#endif
        if (Collision)
        {
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
        }
        else
        {
            Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
            Controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToTarget"), 99999.0f);
        }
    }


}
