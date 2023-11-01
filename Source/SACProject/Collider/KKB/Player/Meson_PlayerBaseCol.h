// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Meson_BaseCol.h"
#include "Meson_PlayerBaseCol.generated.h"

UCLASS()
class SACPROJECT_API AMeson_PlayerBaseCol : public AMeson_BaseCol
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeson_PlayerBaseCol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex) override;
};
