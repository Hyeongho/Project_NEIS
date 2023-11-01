// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Grux_BaseAttackCheck.generated.h"

UENUM(BlueprintType)
enum class EGruxAttackCheck : uint8
{
	Attack,
	Interaction
};

UCLASS()
class SACPROJECT_API UBTDecorator_Grux_BaseAttackCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_Grux_BaseAttackCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EGruxAttackCheck m_CheckType;


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
