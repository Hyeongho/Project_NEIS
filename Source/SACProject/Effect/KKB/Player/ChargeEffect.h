// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ChargeEffect.generated.h"

UCLASS()
class SACPROJECT_API AChargeEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChargeEffect();

protected:
	UPROPERTY(Category = "Body", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent>	m_Body;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetEffectLocation(const FVector& Loc);
	void SetEffectRotation(const FRotator& Rot);

};
