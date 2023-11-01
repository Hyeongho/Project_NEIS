// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEffect.h"
#include "HealPointEffect.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AHealPointEffect : public ABaseEffect
{
	GENERATED_BODY()
	
public:
	AHealPointEffect();

protected:
	UPROPERTY(Category = "HealPointBox", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent>		m_HealBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void HealBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
