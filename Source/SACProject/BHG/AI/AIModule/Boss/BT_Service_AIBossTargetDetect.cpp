// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_AIBossTargetDetect.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"

UBT_Service_AIBossTargetDetect::UBT_Service_AIBossTargetDetect() 
	: Super()
{
	NodeName = TEXT("BossTargetDetect");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBT_Service_AIBossTargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_BossMonster* AIBossMonster = Cast<AAI_BossMonster>(Controller->GetPawn());

		if (!IsValid(AIBossMonster))
			return;

		FHitResult	result;

		FCollisionQueryParams	param(NAME_None, false, AIBossMonster);

		bool Collision = GetWorld()->SweepSingleByChannel(result,
			AIBossMonster->GetActorLocation(), AIBossMonster->GetActorLocation(), FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel9,
			FCollisionShape::MakeSphere(2000.f), param);

#if ENABLE_DRAW_DEBUG

		//FColor	DrawColor = Collision ? FColor::Red : FColor::Green;
		//DrawDebugSphere(GetWorld(), AIBossMonster->GetActorLocation(), 2000.f,	20, DrawColor, false, 0.35f);

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
