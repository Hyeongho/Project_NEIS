// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Grux_IsBerserk.h"
#include "../../Grux_AICharacter.h"

UBTDecorator_Grux_IsBerserk::UBTDecorator_Grux_IsBerserk()
{
	NodeName = TEXT("Grux_Berserk");
}

bool UBTDecorator_Grux_IsBerserk::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (IsValid(GruxCharacter))
		return GruxCharacter->IsBerserk();

	return false;
}
