// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Grux_Alive.h"
#include "../../Grux_AICharacter.h"
#include "../../../AIState.h"

UBTDecorator_Grux_Alive::UBTDecorator_Grux_Alive()
{
	NodeName = TEXT("Grux_Alive");
}

bool UBTDecorator_Grux_Alive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (IsValid(GruxCharacter))
		return GruxCharacter->GetAIState()->GetHP() > 0;

	return false;
}
