// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../DefaultItem.h"
#include "ScoreItem.generated.h"

class UCurveFloat;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AScoreItem : public ADefaultItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScoreItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartMove();
	void FinishMove();

	void MoveToPlayer();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystemComponent> m_TrailComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_TrailParticle;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Curve", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> m_ScoreCurve;

	FTimerHandle m_MoveWaitTimer;
	float m_MoveWaitTime;

	FTimerHandle m_MoveTimer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Curve", meta = (AllowPrivateAccess = true))
	float m_MoveTime;

	bool m_Move;

	FVector m_InitialLocation;
};
