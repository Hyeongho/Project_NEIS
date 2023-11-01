// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIController.h"
#include "IS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AIS_AIController : public ADefaultAIController
{
	GENERATED_BODY()

public:
	AIS_AIController();

protected:
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent>		m_Body;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void SetAttackPossibleToBB(bool Cooldown = true);
	void SetStartToBB(bool isStartNow = false);

public:
	void AttackAction();
	void StampedeAction();
	void EarthquakeAction();
};
