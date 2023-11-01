// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "HitBoxObject.h"
#include "NightmareHitBox.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ANightmareHitBox : public AHitBoxObject
{
	GENERATED_BODY()

public:
	ANightmareHitBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void HitBoxDestroy();

protected:
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	
};
