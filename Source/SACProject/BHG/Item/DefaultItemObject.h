// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DefaultItemObject.generated.h"

UCLASS()
class SACPROJECT_API ADefaultItemObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultItemObject();

protected:
	UPROPERTY(Category = "DefaultBox", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent>		m_DefaultBox;

	UPROPERTY(Category = "Particle", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystemComponent> m_Particle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
