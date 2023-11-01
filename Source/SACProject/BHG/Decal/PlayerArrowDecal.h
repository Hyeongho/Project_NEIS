// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DecalBase.h"
#include "PlayerArrowDecal.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API APlayerArrowDecal : public ADecalBase
{
	GENERATED_BODY()

public:
	APlayerArrowDecal();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
