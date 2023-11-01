// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_AIBossController.h"

ABHG_AIBossController::ABHG_AIBossController()
	:Super()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AIBossTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BHG/Blueprints/AI/BT_AIBoss.BT_AIBoss'"));

	if (AIBossTree.Succeeded())
		m_AITree = AIBossTree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBossBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/BHG/Blueprints/AI/BB_AIBoss.BB_AIBoss'"));

	if (AIBossBlackboard.Succeeded())
		m_AIBlackboard = AIBossBlackboard.Object;

}

void ABHG_AIBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(m_AITree) && IsValid(m_AIBlackboard))
	{

		UBlackboardComponent* BlackBoardRef = Blackboard;

		if (UseBlackboard(m_AIBlackboard, BlackBoardRef))
		{
			RunBehaviorTree(m_AITree);
		}
	}
}

void ABHG_AIBossController::OnUnPossess()
{
	Super::OnUnPossess();
}
