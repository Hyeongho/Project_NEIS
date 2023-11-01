// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../AI/DefaultAIController.h"
#include "BHG_AIBossController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_AIBossController : public ADefaultAIController
{
	GENERATED_BODY()
	
public:
	ABHG_AIBossController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
