// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Effect/DefaultEffect.h"
#include "BaseEffect.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABaseEffect : public ADefaultEffect
{
	GENERATED_BODY()

public:
	ABaseEffect();

protected:
	TObjectPtr<ACharacter>	m_Owner;

	FVector		m_Offset;

public:
	void SetEffectOwner(class ACharacter* EffectOwner);
	void SetOffset(FVector Offset);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void DeleteEffect();

private:
	UFUNCTION()
		void PariticleFinish(UParticleSystemComponent* System);
	
};
