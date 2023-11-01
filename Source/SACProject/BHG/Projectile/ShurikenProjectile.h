// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ProjectileBase.h"
#include "ShurikenProjectile.generated.h"

UCLASS()
class SACPROJECT_API AShurikenProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	AShurikenProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	virtual void ProjectileFire(FVector Velocity, class ACharacter* Shooter);

private:
	virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
