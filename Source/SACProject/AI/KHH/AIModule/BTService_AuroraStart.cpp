// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AuroraStart.h"
#include "../../AIState.h"
#include "../AuroraAICharacter.h"

UBTService_AuroraStart::UBTService_AuroraStart()
{
	NodeName = TEXT("AuroraStart");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_AuroraStart::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (IsValid(Aurora))
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("Start"), Aurora->GetStartEnd());
	}
}
