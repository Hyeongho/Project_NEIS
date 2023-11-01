// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Grux_Earthquake_Lava.generated.h"

UCLASS()
class SACPROJECT_API AGrux_Earthquake_Lava : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrux_Earthquake_Lava();


protected:
	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> m_Body;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> m_LavaEffect;

private:
	int32 m_DamageRelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void DecalEnd();
	void SetDamage(int32 Damage) { m_DamageRelay = Damage; }

protected:
	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);
};
