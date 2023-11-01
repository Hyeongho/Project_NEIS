// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DefaultSpawnObject.h"
#include "BossSpawnObject.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABossSpawnObject : public ADefaultSpawnObject
{
	GENERATED_BODY()

public:
	ABossSpawnObject();

protected:
	UPROPERTY(Category = "BossClass", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AAI_BossMonster>	m_BossMonster;


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
