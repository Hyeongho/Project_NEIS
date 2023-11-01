// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Meson_AICollider.h"
#include "Grux_EarthquakeCol.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AGrux_EarthquakeCol : public AMeson_AICollider
{
	GENERATED_BODY()

public:
	AGrux_EarthquakeCol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
};
