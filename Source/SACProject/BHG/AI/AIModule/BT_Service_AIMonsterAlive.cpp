// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_AIMonsterAlive.h"
#include "../AI_Monster.h"
#include "../../Animation/BHG_AIAnimInstance.h"

UBT_Service_AIMonsterAlive::UBT_Service_AIMonsterAlive()
	: Super()
{
	NodeName = TEXT("MonsterAlive");

	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBT_Service_AIMonsterAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_Monster* AIMonster = Cast<AAI_Monster>(Controller->GetPawn());

		if (IsValid(AIMonster))
		{
			UBHG_AIAnimInstance* AIAnim = Cast<UBHG_AIAnimInstance>(AIMonster->GetMesh()->GetAnimInstance());

			if (!AIAnim->GetHitEnable() && AIMonster->GetRespawnOn())
			{
				if(AIAnim->GetMonsterAnimType() != EAIMonsterAnimType::Die)				
				Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Owner"), AIMonster);
			}
		
		}

		else
		{
			Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Owner"), nullptr);
		}
	}
}
