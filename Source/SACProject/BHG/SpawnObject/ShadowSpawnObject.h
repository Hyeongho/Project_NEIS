// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "DefaultSpawnObject.h"
#include "ShadowSpawnObject.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShadowSpawnObject : public ADefaultSpawnObject
{
	GENERATED_BODY()

public:
	AShadowSpawnObject();

protected:
	UPROPERTY(Category = "Shadow", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABHG_UltimateShadow>	m_UltimateShadow;

	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AProjectileBase >> m_UltimateProjectile;

	UPROPERTY(Category = "ShadowOffset", EditAnywhere, BlueprintReadWrite)
	float	m_ShadowOffset;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>	m_UltimateEffect;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>	m_AuraEffect;


	bool	m_SkillStart;

	float	m_SkillTime;

	int32	m_ProjectieNum;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

public:
	void UltimateSkillStart();

	void SpawnerDestory();
	void SpawnerEffect();



};
