// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CloseEnoughToTarget.h"
#include "ShooterMonster.h"
#include "../AIState.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTDecorator_CloseEnoughToTarget::UBTDecorator_CloseEnoughToTarget()
	: Super()
{
	NodeName = TEXT("CloseEnoughToTarget");
}

bool UBTDecorator_CloseEnoughToTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetCharacter());
	if (IsValid(Monster))
	{
		float AttackDistance = Controller->GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackDistance"));

		float DistanceToTarget = Controller->GetBlackboardComponent()->GetValueAsFloat(TEXT("DistanceToTarget"));

		return DistanceToTarget <= AttackDistance;
	}

	return false;
}
