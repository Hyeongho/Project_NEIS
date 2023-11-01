// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SoundPlayer.generated.h"

UCLASS()
class SACPROJECT_API ASoundPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundPlayer();

protected:
	UPROPERTY(Category = "AudioComp", EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAudioComponent>	m_AudioComp;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite)
		TObjectPtr<USoundBase>	m_Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void SoundReplay();

public:
	void ChangeSound();
	void PauseSound();

};
