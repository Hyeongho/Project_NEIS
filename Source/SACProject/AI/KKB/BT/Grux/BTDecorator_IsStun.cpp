// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsStun.h"
#include "../../Grux_AICharacter.h"

UBTDecorator_IsStun::UBTDecorator_IsStun()
{
	NodeName = TEXT("Grux_IsStun");
}

bool UBTDecorator_IsStun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (IsValid(GruxCharacter))
		return GruxCharacter->IsStun();

	return false;
}
