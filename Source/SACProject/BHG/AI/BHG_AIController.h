// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../../AI/DefaultAIController.h"
#include "BHG_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_AIController : public ADefaultAIController
{
	GENERATED_BODY()

public:
	ABHG_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
