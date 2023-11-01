// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IS_Alive.h"
#include "../../IS_AICharacter.h"
#include "../../../AIState.h"

UBTDecorator_IS_Alive::UBTDecorator_IS_Alive()
{
	NodeName = TEXT("IS_Alive");
}

bool UBTDecorator_IS_Alive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AIS_AICharacter* Monster = Cast<AIS_AICharacter>(Controller->GetCharacter());

	if (IsValid(Monster))
		return Monster->GetAIState()->GetHP() > 0;

	return false;
}
