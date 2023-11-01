// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../Player/PlayerCharacter.h"
#include "BHG_Player.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_Player : public APlayerCharacter
{
	GENERATED_BODY()

public:
	ABHG_Player();

protected:
	TObjectPtr<class ABHG_ShadowPlayer>	m_ShadowPlayer;

	UPROPERTY(Category = "ArrowDecal", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ADecalBase>	m_ArrowDecal;

	UPROPERTY(Category = "Ghost", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AGhostActor>		m_Ghost;

protected:
	//Ability
	UPROPERTY(Category = "AbilityComponent", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAbilityComponent>		m_Ability;

	UPROPERTY(Category = "PlayerSound", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAudioComponent>	m_Audio;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_DefaultAttack;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_ShurikenAttack;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_CounterAttack;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_Nightmare;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_ShadowPartner;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_Ultimate;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDefaultAbility>	m_Evade;

	UPROPERTY(Category = "HealEffect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>	m_HealEffect;



	bool EvadeOn;
	float GhostTime;

	float RecoveryMPTime;

	FTimerHandle m_ShadowTimerHandle;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void OnDamaged(int32 Damage, class ACharacter* Shooter, class ACharacter* Target, bool Counter);


public:
	void SetShadowPlayer(class ABHG_ShadowPlayer* ShadowPlayer);
	void SetEvadeOn(bool On) { EvadeOn = On; }
	void StartHealEffect();
	void PlayAudio();




private:
	void ShadowOff();



public:
	// Move Bind
	void MoveAxis(const FInputActionValue& Value);


	// Ability Bind
	void DefaultAttackKey();
	void ShurikenAttackkey();
	void CounterAttackKey();
	void NightmareKey();
	void ShadowPartnerKey();
	void UltimateKey();
	void EvadeKey();
};
