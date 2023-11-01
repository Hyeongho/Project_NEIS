// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_AIMonsterTargetDetect.h"
#include "../AI_Monster.h"

UBT_Service_AIMonsterTargetDetect::UBT_Service_AIMonsterTargetDetect()
	: Super()
{
	NodeName = TEXT("TargetDetect");
	Interval = 0.5f; 
	RandomDeviation = 0.1f; 
}

void UBT_Service_AIMonsterTargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

		if (!IsValid(AIMonster))
			return;

		FHitResult	result;

		FCollisionQueryParams	param(NAME_None, false, AIMonster);

		bool Collision = GetWorld()->SweepSingleByChannel(result,
			AIMonster->GetActorLocation(), AIMonster->GetActorLocation(), FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel9,
			FCollisionShape::MakeSphere(1500.f), param);

#if ENABLE_DRAW_DEBUG


		//FColor	DrawColor = Collision ? FColor::Red : FColor::Green;


		//DrawDebugSphere(GetWorld(), AIMonster->GetActorLocation(), 800.f,
		//	20, DrawColor, false, 0.35f);

#endif


		if (Collision)
		{
			Controller->GetBlackboardComponent()->SetValueAsObject(
				TEXT("Target"), result.GetActor());
		}

		else
		{
			Controller->GetBlackboardComponent()->SetValueAsObject(
				TEXT("Target"), nullptr);
		}
	}
}
