// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMonsterController.h"

AShooterMonsterController::AShooterMonsterController()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/CJH/Blueprints/Enemy/AI/BT_ShooterMonster.BT_ShooterMonster'"));
	if (AITree.Succeeded())
		m_AITree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/CJH/Blueprints/Enemy/AI/BB_ShooterMonster.BB_ShooterMonster'"));
	if (AIBlackboard.Succeeded())
		m_AIBlackboard = AIBlackboard.Object;
}

void AShooterMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(m_AITree) && IsValid(m_AIBlackboard))
	{
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(m_AIBlackboard, BlackboardRef))
		{
			RunBehaviorTree(m_AITree);

			BlackboardRef->SetValueAsFloat(TEXT("DistanceToTarget"), 99999.0f);
		}
	}
}

void AShooterMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}
