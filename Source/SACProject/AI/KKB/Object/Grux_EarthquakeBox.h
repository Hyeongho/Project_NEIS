// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Grux_EarthquakeBox.generated.h"

class UCoolDownComponent;

UCLASS()
class SACPROJECT_API AGrux_EarthquakeBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrux_EarthquakeBox();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCoolDownComponent> m_LavaSpawnCooldown;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_SpawnCycleTime;


	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_BoxXSize;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_BoxYSize;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_BoxLifeSpan;

private:
	int32 m_DamageRelay;

public:
	void SetDemage(int32 Damage) { m_DamageRelay = Damage; }


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
