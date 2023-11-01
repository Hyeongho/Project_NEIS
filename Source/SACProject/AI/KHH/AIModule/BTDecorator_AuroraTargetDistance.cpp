// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AuroraTargetDistance.h"
#include "../AuroraAICharacter.h"
#include "../../AIState.h"

UBTDecorator_AuroraTargetDistance::UBTDecorator_AuroraTargetDistance()
{
	NodeName = TEXT("AuroraTargetDistance");

	m_CheckType = EAuroraDistanceType::Interaction;
}

bool UBTDecorator_AuroraTargetDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (!IsValid(Aurora))
	{
		return false;
	}

	float TypeDistance = 0.f;

	switch (m_CheckType)
	{
	case EAuroraDistanceType::Attack:
		TypeDistance = Aurora->GetAIState()->GetAttackDistance();
		break;
	case EAuroraDistanceType::Interaction:
		TypeDistance = Aurora->GetAIState()->GetInteractionDistance();
		break;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		return false;
	}

	FVector	AILoc = Aurora->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z -= Aurora->GetHalfHeight();
	TargetLoc.Z -= Aurora->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	// 거리에서 각 물체들의 캡슐 반경을 빼준다.
	Distance -= Aurora->GetCapsuleRadius();

	// Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	return Distance <= TypeDistance;
}
