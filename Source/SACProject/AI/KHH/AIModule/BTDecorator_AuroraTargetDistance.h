// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AuroraTargetDistance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAuroraDistanceType : uint8
{
	Attack,
	Interaction
};

UCLASS()
class SACPROJECT_API UBTDecorator_AuroraTargetDistance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_AuroraTargetDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAuroraDistanceType m_CheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
