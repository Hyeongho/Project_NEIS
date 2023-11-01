// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_AIController.h"

ABHG_AIController::ABHG_AIController()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/BHG/Blueprints/AI/BT_AIDefault.BT_AIDefault'"));

	if (AITree.Succeeded())
		m_AITree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/BHG/Blueprints/AI/BB_AIDefault.BB_AIDefault'"));

	if (AIBlackboard.Succeeded())
		m_AIBlackboard = AIBlackboard.Object;

}

void ABHG_AIController::OnPossess(APawn* InPawn)
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

void ABHG_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}
