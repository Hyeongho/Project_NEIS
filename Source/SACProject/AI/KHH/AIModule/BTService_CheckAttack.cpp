// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAttack.h"
#include "../AuroraAICharacter.h"
#include "../../AIState.h"


UBTService_CheckAttack::UBTService_CheckAttack()
{
	NodeName = TEXT("CheckAttack");

	bNotifyTick = true;

	bNotifyOnSearch = true;
}

void UBTService_CheckAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(Controller->GetCharacter());

	if (!IsValid(Aurora))
	{
		return;
	}

	TArray<int32> AttackIndex;

	AttackIndex.Add(3);

	int size = Aurora->GetSkillCoolTimeArray().Num();

	for (int i = 0; i < size; i++)
	{
		if (!Aurora->GetIsCool(i))
		{
			AttackIndex.Add(i);
		}
	}

	int32 RandomAttackIndex = FMath::RandRange(0, AttackIndex.Num() - 1);
	int SelectAttack = AttackIndex[RandomAttackIndex];

	Controller->GetBlackboardComponent()->SetValueAsInt(TEXT("AttackIndex"), SelectAttack);
}

void UBTService_CheckAttack::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}
