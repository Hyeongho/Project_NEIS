// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IS_AttackCheck.h"
#include "../../IS_AICharacter.h"
#include "../../../AIState.h"

UBTDecorator_IS_AttackCheck::UBTDecorator_IS_AttackCheck()
{
    NodeName = TEXT("IS_AttackCheck");
}

bool UBTDecorator_IS_AttackCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AIS_AICharacter* ISCharacter = Cast<AIS_AICharacter>(Controller->GetCharacter());

	if (!IsValid(ISCharacter))
		return false;

	float TypeDistance = 0.f;

	switch (m_CheckType)
	{
	case EISAttackCheck::Attack:
		TypeDistance = ISCharacter->GetAIState()->GetAttackDistance();
		break;
	case EISAttackCheck::Interaction:
		TypeDistance = ISCharacter->GetAIState()->GetInteractionDistance();
		break;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
		return false;

	FVector	AILoc = ISCharacter->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z = 0.f;
	TargetLoc.Z = 0.f;

	float Distance = FVector::Distance(AILoc, TargetLoc);

	return Distance <= TypeDistance;
}
