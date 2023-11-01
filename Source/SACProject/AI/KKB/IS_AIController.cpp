// Fill out your copyright notice in the Description page of Project Settings.


#include "IS_AIController.h"

AIS_AIController::AIS_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/KKB/AI/IggyScorch/BT_IS.BT_IS'"));

	if (AITree.Succeeded())
		m_AITree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/KKB/AI/IggyScorch/BB_IS.BB_IS'"));

	if (AIBlackboard.Succeeded()) 
		m_AIBlackboard = AIBlackboard.Object;
}

void AIS_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(m_AITree) && IsValid(m_AIBlackboard))
	{
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(m_AIBlackboard, BlackboardRef))
			RunBehaviorTree(m_AITree);
	}


	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackPossible"), true);
	GetBlackboardComponent()->SetValueAsBool(TEXT("Start"), true);
}

void AIS_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AIS_AIController::SetAttackPossibleToBB(bool Cooldown)
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackPossible"), Cooldown);
}

void AIS_AIController::SetStartToBB(bool isStartNow)
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("Start"), isStartNow);
}
