// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckTargetDistance.generated.h"

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8
{
	Attack,
	Interaction
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorator_CheckTargetDistance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckTargetDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ECheckDistanceType	mCheckType;


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const;
	
};
