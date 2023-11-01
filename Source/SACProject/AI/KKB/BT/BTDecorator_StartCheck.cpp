// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_StartCheck.h"

UBTDecorator_StartCheck::UBTDecorator_StartCheck()
{
	NodeName = TEXT("StartCheck");
}

bool UBTDecorator_StartCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	return Controller->GetBlackboardComponent()->GetValueAsBool(TEXT("Start"));
}
