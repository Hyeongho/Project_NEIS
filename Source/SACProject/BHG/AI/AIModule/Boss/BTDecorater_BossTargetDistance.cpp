// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorater_BossTargetDistance.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"

UBTDecorater_BossTargetDistance::UBTDecorater_BossTargetDistance()
	:Super()
{
	mCheckType = EBossCheckDistanceType::Interaction;
}

bool UBTDecorater_BossTargetDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_BossMonster* AIBossMonster = Cast<AAI_BossMonster>(Controller->GetPawn());

		if (!IsValid(AIBossMonster))
			return false;

		float TypeDistance = 0.f;

		switch (mCheckType)
		{
		case EBossCheckDistanceType::Attack:
			TypeDistance = 250.f;
			break;
		case EBossCheckDistanceType::Interaction:
			TypeDistance = 2000.f;
			break;
		}

		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (!IsValid(Target))
			return false;


		FVector	AILoc = AIBossMonster->GetActorLocation();
		FVector	TargetLoc = Target->GetActorLocation();

		FVector TargetAxis = TargetLoc - AILoc;

		AILoc.Z -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		TargetLoc.Z -= Cast<ACharacter>(Target)->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		float Distance = FVector::Distance(AILoc, TargetLoc);

		Distance -= AIBossMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();

		UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (IsValid(Capsule))
		{
			Distance -= Capsule->GetScaledCapsuleRadius();
		}

		return Distance <= TypeDistance;

	}

	return false;
}
