// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_MonsterIsAlive.h"
#include "ShooterMonster.h"

UBTDecorator_MonsterIsAlive::UBTDecorator_MonsterIsAlive()
	: Super()
{
	NodeName = TEXT("MonsterIsAlive");
}

bool UBTDecorator_MonsterIsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AShooterMonster* Monster = Cast<AShooterMonster>(Controller->GetCharacter());
	if (IsValid(Monster))
	{
		return Monster->IsAlive();
	}

	return false;
}
