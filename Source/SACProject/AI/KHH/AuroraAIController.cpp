// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAIController.h"

AAuroraAIController::AAuroraAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/KHH/AI/BT_AuroraAI.BT_AuroraAI'"));

	if (AITree.Succeeded())
	{
		m_AITree = AITree.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/KHH/AI/BB_AuroraAI.BB_AuroraAI'"));

	if (AIBlackboard.Succeeded())
	{
		m_AIBlackboard = AIBlackboard.Object;
	}
}

void AAuroraAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(m_AITree) && IsValid(m_AIBlackboard))
	{
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(m_AIBlackboard, BlackboardRef))
		{
			RunBehaviorTree(m_AITree);
		}
	}
}

void AAuroraAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
