// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacter.h"
#include "TerraCharacter.generated.h"

UENUM(BlueprintType)
enum class ETerraType : uint8
{
	Default, 
	Gurad
};

UCLASS()
class SACPROJECT_API ATerraCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ATerraCharacter();

private:
	ETerraType m_TerraType;

	TObjectPtr<class UFrozenCaveWidget> m_FrozenCaveWidget;

	float m_MPRecovery;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetTerraType(ETerraType Type)
	{
		m_TerraType = Type;
	}

	ETerraType GetTerraType() const
	{
		return m_TerraType;
	}

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void Attack();
};
