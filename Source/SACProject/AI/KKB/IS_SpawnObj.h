// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "IS_SpawnObj.generated.h"

class AIS_AICharacter;
class UCoolDownComponent;

UCLASS()
class SACPROJECT_API AIS_SpawnObj : public AActor
{
	GENERATED_BODY()
	
public:	
	AIS_SpawnObj();

protected:
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent>		m_Body;

	// CoolTime Component
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCoolDownComponent> m_MonsterRespawnCooldown;

	// Effect Component
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> m_RespawnEffect;

	// Normal Death Count >= m_EliteSpawnCount ? EliteSpawn
	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32	m_NormalSpawnCount;

	// IS Spawn Time
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_ISSpawnTime;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_ISSpawnRangeTime;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_ISSpawnIsRand;

	// IS Max Count
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_ISSpawnMaxCount;

	// IS Max Count
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_IsSpawnStart;

private:
	float m_SpawnWaitTime;
	float m_SpawnWaitMaxTime;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnMonster(bool IsElite = false);
	void PlayEffect();

public:
	UFUNCTION(BlueprintCallable)
	void SpawnStart() { m_IsSpawnStart = true; }

protected:
	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);

};
