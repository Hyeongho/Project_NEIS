// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Grux_StampedeReady.h"
#include "../../Grux_AICharacter.h"

UBTDecorator_Grux_StampedeReady::UBTDecorator_Grux_StampedeReady()
{
	NodeName = TEXT("Grux_Stampede_Ready");
}

bool UBTDecorator_Grux_StampedeReady::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (IsValid(GruxCharacter)) {
		// BT 에러 막기 위해 사망 체크 추가
		if (GruxCharacter->IsDead())
			return false;


		return GruxCharacter->IsStampedeActive();
	}

	return false;
}
