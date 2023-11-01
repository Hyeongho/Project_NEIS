// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../AI/AICharacter.h"
#include "DefaultAICharacter.generated.h"
UCLASS()
class SACPROJECT_API ADefaultAICharacter : public AAICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultAICharacter();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void OnDamaged(int32 Damage, class ACharacter* Shooter, class ACharacter* Target, bool Counter);

public:
	float GetCapusuleHalfHeight();
	
};
