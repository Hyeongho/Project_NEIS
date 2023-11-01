// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DefaultSpawnObject.h"
#include "BossRockSpawnObject.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABossRockSpawnObject : public ADefaultSpawnObject
{
	GENERATED_BODY()


public:
	ABossRockSpawnObject();

protected:
	UPROPERTY(Category = "RockObject", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABossSkill1Object>	m_RockObject;

	UPROPERTY(Category = "RespawnTime", EditAnywhere, BlueprintReadWrite)
	float RespawnTime;

	UPROPERTY(Category = "SpawnCount", EditAnywhere, BlueprintReadWrite)
	int32	SpawnCount;

	float CurruntTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
