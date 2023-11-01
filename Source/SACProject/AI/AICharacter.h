// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class SACPROJECT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	static TObjectPtr<UDataTable> m_AIDataTable;

public:
	static void LoadAIData();

protected:
	static const FAIDataTable* FindAIData(const FName& Name);

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIState> m_AIState;

	UPROPERTY(Category = Component, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName m_Name;

	TObjectPtr<class UDefaultAIAnimInstance> m_Anim;

public:
	const TObjectPtr<class UAIState>& GetAIState() const
	{
		return m_AIState;
	}

	const TObjectPtr<class UDefaultAIAnimInstance>& GetAIAnimInstance()	const
	{
		return m_Anim;
	}

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
