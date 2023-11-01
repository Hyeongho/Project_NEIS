// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIController.h"
#include "Grux_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AGrux_AIController : public ADefaultAIController
{
	GENERATED_BODY()
	
public:
	AGrux_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void SetStartToBB(bool isStartNow = false);
	FVector GetTargetPosByBB() const;
};
