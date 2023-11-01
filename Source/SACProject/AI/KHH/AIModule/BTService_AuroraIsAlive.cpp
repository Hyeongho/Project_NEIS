// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AuroraIsAlive.h"
#include "../AuroraAICharacter.h"
#include "../../AIState.h"

UBTService_AuroraIsAlive::UBTService_AuroraIsAlive()
{
	NodeName = TEXT("AuroraIsAlive");

	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_AuroraIsAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* AICharacter = Cast<AAuroraAICharacter>(Controller->GetPawn());

	if (IsValid(AICharacter))
	{
		Controller->GetBlackboardComponent()->SetValueAsInt(TEXT("HP"), AICharacter->GetAIState()->GetHP());
	}
}
