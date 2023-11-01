// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorater_BossTargetDistance.generated.h"

UENUM(BlueprintType)
enum class EBossCheckDistanceType : uint8
{
	Attack,
	Interaction
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBTDecorater_BossTargetDistance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorater_BossTargetDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EBossCheckDistanceType	mCheckType;


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const;
	
};
