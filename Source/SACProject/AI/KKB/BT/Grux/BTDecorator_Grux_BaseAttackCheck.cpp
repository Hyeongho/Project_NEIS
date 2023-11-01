// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Grux_BaseAttackCheck.h"
#include "../../Grux_AICharacter.h"
#include "../../../AIState.h"

UBTDecorator_Grux_BaseAttackCheck::UBTDecorator_Grux_BaseAttackCheck()
{
	NodeName = TEXT("Grux_BaseAttackCheck");
}

bool UBTDecorator_Grux_BaseAttackCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (!IsValid(GruxCharacter))
		return false;


	// BT 에러 막기 위해 사망 체크 추가
	if (GruxCharacter->IsDead())
		return false;


	float TypeDistance = 0.f;

	switch (m_CheckType)
	{
	case EGruxAttackCheck::Attack:
		TypeDistance = GruxCharacter->GetAIState()->GetAttackDistance();
		break;
	case EGruxAttackCheck::Interaction:
		TypeDistance = GruxCharacter->GetAIState()->GetInteractionDistance();
		break;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
		return false;

	FVector	AILoc = GruxCharacter->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z = 0.f;
	TargetLoc.Z = 0.f;

	float Distance = FVector::Distance(AILoc, TargetLoc);

	return Distance <= TypeDistance;
}
