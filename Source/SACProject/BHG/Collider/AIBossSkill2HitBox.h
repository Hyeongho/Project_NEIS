// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HitBoxObject.h"
#include "AIBossSkill2HitBox.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AAIBossSkill2HitBox : public AHitBoxObject
{
	GENERATED_BODY()

public:
	AAIBossSkill2HitBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void HitBoxDestroy() override;

protected:
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;


	
};
