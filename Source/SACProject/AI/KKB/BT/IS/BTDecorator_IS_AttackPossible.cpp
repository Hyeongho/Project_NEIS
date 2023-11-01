// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IS_AttackPossible.h"

UBTDecorator_IS_AttackPossible::UBTDecorator_IS_AttackPossible()
{
	NodeName = TEXT("IS_AttackPossible");
}

bool UBTDecorator_IS_AttackPossible::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	return Controller->GetBlackboardComponent()->GetValueAsBool(TEXT("AttackPossible"));
}
