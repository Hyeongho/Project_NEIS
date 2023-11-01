// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ShooterMonsterSpawner.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShooterMonster;
class USoundCue;
class UParticleSystem;

UCLASS()
class SACPROJECT_API AShooterMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShooterMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartSpawn();

	void ResetSpawn();

	void SpawnMonster();


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> m_BoxBound;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> m_SpawnerMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystemComponent> m_TrailComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_TrailParticle;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue>	m_SpawnSound;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_SpawnParticle;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AShooterMonster>> m_MonsterList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	int32 m_SpawnCount;

	FTimerHandle m_SpawnTimer;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	float m_SpawnTime;

	int32 m_CurrentSpawnCount;
};
