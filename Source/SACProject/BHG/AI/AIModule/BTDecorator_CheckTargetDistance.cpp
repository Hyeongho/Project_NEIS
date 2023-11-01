// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckTargetDistance.h"
#include "../AI_Monster.h"

UBTDecorator_CheckTargetDistance::UBTDecorator_CheckTargetDistance()
	: Super()
{
	mCheckType = ECheckDistanceType::Interaction;
}

bool UBTDecorator_CheckTargetDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

		if (!IsValid(AIMonster))
			return false;

		float TypeDistance = 0.f;

		switch (mCheckType)
		{
		case ECheckDistanceType::Attack:
			TypeDistance = 100.f;
			break;
		case ECheckDistanceType::Interaction:
			TypeDistance = 1500.f;
			break;
		}

		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (!IsValid(Target))
			return false;	


		FVector	AILoc = AIMonster->GetActorLocation();
		FVector	TargetLoc = Target->GetActorLocation();

		FVector TargetAxis = TargetLoc - AILoc;

		AILoc.Z -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		TargetLoc.Z -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		float Distance = FVector::Distance(AILoc, TargetLoc);

		Distance -= AIMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();
	
		UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (IsValid(Capsule))
		{
			Distance -= Capsule->GetScaledCapsuleRadius();
		}

		return Distance <= TypeDistance;

	}

	return false;

}

