// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Grux_EarthquakeReady.h"
#include "../../Grux_AICharacter.h"

UBTDecorator_Grux_EarthquakeReady::UBTDecorator_Grux_EarthquakeReady()
{
	NodeName = TEXT("Grux_Earthquake_Ready");
}

bool UBTDecorator_Grux_EarthquakeReady::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetCharacter());

	if (IsValid(GruxCharacter))
		return GruxCharacter->IsEarthquakeActive();

	return false;
}
