// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIController.h"
#include "AuroraAIController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AAuroraAIController : public ADefaultAIController
{
	GENERATED_BODY()
	
public:
	AAuroraAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
