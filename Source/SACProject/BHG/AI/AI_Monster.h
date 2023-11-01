// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultAICharacter.h"
#include "AI_Monster.generated.h"

class UDamageTextWidget;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AAI_Monster : public ADefaultAICharacter
{
	GENERATED_BODY()

public:
	AAI_Monster();

protected:
	//Ability
	UPROPERTY(Category = "AbilityComponent", EditAnywhere, BlueprintReadOnly)
		TObjectPtr<class UAbilityComponent>		m_Ability;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_DefaultAttack;

	UPROPERTY(Category = "HealItem", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseEffect>	m_HealItem;

	UPROPERTY(Category = "WidgetComp", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent>		m_Widget;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;

	TObjectPtr<class AMonsterSpawnObject>	m_Spawner;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;


	
	bool	HitOn;
	float	HitTime;

	float	RespawnTime;
	bool	RespawnOn;



public:
	const bool& GetRespawnOn() { return RespawnOn; }

public:
	void SetSpawner(class AMonsterSpawnObject* OwnerSpawn);


protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnDamaged(int32 Damage, class ACharacter* Shooter, class ACharacter* Target, bool Counter) override;

public:
	void DefaultAttack();
	
};
