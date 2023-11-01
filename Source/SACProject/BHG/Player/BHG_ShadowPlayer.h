// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Player/PlayerCharacter.h"
#include "BHG_ShadowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_ShadowPlayer : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ABHG_ShadowPlayer();

protected:
	UPROPERTY(Category = "AbilityComponent", EditAnywhere, BlueprintReadOnly)
		TObjectPtr<class UAbilityComponent>		m_Ability;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_DefaultAttack;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_ShurikenAttack;

	TObjectPtr<class ABHG_Player>	m_Player;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>	m_ShadowEffect;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetPlayer(class ABHG_Player* Player);

	// Attack Bind
	void DefaultAttackKey();
	void ShurikenAttackkey();
};
