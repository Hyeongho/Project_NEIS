// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileBase.h"
#include "UltimateProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AUltimateProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	AUltimateProjectile();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

public:
	virtual void ProjectileFire(FVector Velocity, class ACharacter* Shooter) override;

protected:
	virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
