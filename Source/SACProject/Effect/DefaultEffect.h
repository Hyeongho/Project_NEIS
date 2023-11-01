// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DefaultEffect.generated.h"

UCLASS()
class SACPROJECT_API ADefaultEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultEffect();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> m_Particle;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent>	m_Audio;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetParticleAsset(const FString& Path);
	virtual void SetParticleAsset(UParticleSystem* Particle);
	virtual void SetAudioAsset(const FString& Path);
	virtual void SetAudioAsset(USoundBase* Sound);

};
