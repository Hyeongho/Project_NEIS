// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../DefaultAIController.h"
#include "ShooterMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterMonsterController : public ADefaultAIController
{
	GENERATED_BODY()

public:
	AShooterMonsterController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
