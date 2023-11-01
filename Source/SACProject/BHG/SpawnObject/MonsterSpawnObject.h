// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultSpawnObject.h"
#include "MonsterSpawnObject.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AMonsterSpawnObject : public ADefaultSpawnObject
{
	GENERATED_BODY()

public:
	AMonsterSpawnObject();

protected:
	UPROPERTY(Category = "Monster", EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AAI_Monster>>		m_Monsters;

	UPROPERTY(Category = "MonsterMaxCount", EditAnywhere, BlueprintReadWrite)
	int32	m_MonsterCount;

	UPROPERTY(Category = "MonsterRespawnTime", EditAnywhere, BlueprintReadWrite)
	float	m_RespawnTime;

	int32	m_LiveMonster;

	float	m_Time;


	float	m_StartTime;
	bool	m_Start;

public:
	void MonsterDie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
