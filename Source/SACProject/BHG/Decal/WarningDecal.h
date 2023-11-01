// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DecalBase.h"
#include "WarningDecal.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AWarningDecal : public ADecalBase
{
	GENERATED_BODY()

public:
	AWarningDecal();

protected:
	UPROPERTY(Category = "MaxScale", EditAnywhere, BlueprintReadWrite)
	float MinScale;

	UPROPERTY(Category = "MaxScale", EditAnywhere, BlueprintReadWrite)
	float MaxScale;

	UPROPERTY(Category = "ScaleSpeed", EditAnywhere, BluePrintReadWrite)
	float ScaleSpeed;

	bool  MaxOn;

protected:
	float ScaleTime;
	float AddTime;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
