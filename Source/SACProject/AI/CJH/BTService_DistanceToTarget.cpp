// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DistanceToTarget.h"
#include "ShooterMonster.h"
#include "../AIState.h"	

UBTService_DistanceToTarget::UBTService_DistanceToTarget()
	: Super()
{
	NodeName = TEXT("DistanceToTarget");

	Interval = 0.2f;
	RandomDeviation = 0.1f;
}

void UBTService_DistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();

    if (IsValid(Controller))
    {
        AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetPawn());

        if (!IsValid(Monster))
            return;

        UObject* Target = Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
        if (AActor* TargetActor = Cast<AActor>(Target))
            Controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToTarget"), TargetActor->GetDistanceTo(Monster));

        else
            Controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToTarget"), 99999.0f);
    }
}
