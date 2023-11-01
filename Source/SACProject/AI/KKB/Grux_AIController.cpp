// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_AIController.h"

AGrux_AIController::AGrux_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/KKB/AI/Grux/BT_Grux.BT_Grux'"));

	if (AITree.Succeeded())
		m_AITree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/KKB/AI/Grux/BB_Grux.BB_Grux'"));

	if (AIBlackboard.Succeeded())
		m_AIBlackboard = AIBlackboard.Object;
}

void AGrux_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(m_AITree) && IsValid(m_AIBlackboard))
	{
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(m_AIBlackboard, BlackboardRef))
			RunBehaviorTree(m_AITree);
	}


	GetBlackboardComponent()->SetValueAsBool(TEXT("Start"), true);
}

void AGrux_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AGrux_AIController::SetStartToBB(bool isStartNow)
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("Start"), isStartNow);
}

FVector AGrux_AIController::GetTargetPosByBB() const
{
	AActor* PlayerActor = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	return PlayerActor->GetActorLocation();
}
