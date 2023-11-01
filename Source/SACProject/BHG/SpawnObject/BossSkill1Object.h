// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BossSkill1Object.generated.h"

UCLASS()
class SACPROJECT_API ABossSkill1Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSkill1Object();

protected:
	UPROPERTY(Category = "Decal", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADecalBase>	WarningDecal;

	UPROPERTY(Category = "Projectile", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AProjectileBase>	RockProjectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void DecalEnd();

};
