// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AuroraTargetDetect.h"
#include "../../AIState.h"
#include "../AuroraAICharacter.h"

UBTService_AuroraTargetDetect::UBTService_AuroraTargetDetect()
{
	NodeName = TEXT("AuroraTargetDetect");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_AuroraTargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (!IsValid(Aurora))
	{
		return;
	}

	Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), GetWorld()->GetFirstPlayerController()->GetCharacter());

	/*FVector	AILoc = Aurora->GetActorLocation();

	AILoc.Z -= Aurora->GetHalfHeight();

	FHitResult result;

	FCollisionQueryParams param(NAME_None, false, Aurora);

	bool Collision = GetWorld()->SweepSingleByChannel(result, AILoc, AILoc, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(Aurora->GetAIState()->GetInteractionDistance()), param);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AILoc, Aurora->GetAIState()->GetInteractionDistance(), 20, DrawColor, false, 0.35f);

#endif

	if (Collision)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}

	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}*/
}
