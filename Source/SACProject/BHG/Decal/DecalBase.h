// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Engine/DecalActor.h"
#include "DecalBase.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ADecalBase : public ADecalActor
{
	GENERATED_BODY()

public:
	ADecalBase();

protected:
	TObjectPtr<AActor>		m_DecalOwner;

public:
	void SetDecalOwner(class AActor* DecalOwner);

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
