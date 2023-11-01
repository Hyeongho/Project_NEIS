// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultAICharacter.h"
#include "AI_BossMonster.generated.h"

class UDamageTextWidget;
/**
 * 
 */
UCLASS()
class SACPROJECT_API AAI_BossMonster : public ADefaultAICharacter
{
	GENERATED_BODY()

public:
	AAI_BossMonster();

protected:
	//Ability
	UPROPERTY(Category = "AbilityComponent", EditAnywhere, BlueprintReadOnly)
		TObjectPtr<class UAbilityComponent>		m_Ability;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_DefaultAttack;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_DefaultAttack2;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_Skill1;

	UPROPERTY(Category = "Ability", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UDefaultAbility>	m_Skill2;

	UPROPERTY(Category = "CounterSuccessEffect", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseEffect>	m_CounterSuccessEffect;

	UPROPERTY(Category = "BossCutSceneEffect", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseEffect>	m_CutSceneEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
		TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;


	


protected:
	bool		CounterAttackState;
	bool		BossGlowEnable;
	bool		StartEnable;


	float TestTime;
	float GlowTime;

	float	RespawnTime;
	bool	RespawnOn;

	bool    AbilityEnable;

	bool	BossDie;

	int32 m_BossHP;

	bool	TestAbilityOn;
	float AbilityTime;

public:
	const bool& GetRespawnOn() { return RespawnOn; }
	const int32& GetBossHP() { return m_BossHP; }
	const bool& GetBossDie() { return BossDie; }

public:
	const bool& GetCounterState() { return CounterAttackState; }

public:
	void SetCounterState(bool State) { CounterAttackState = State; }
	void SetRespawnOn();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnDamaged(int32 Damage, class ACharacter* Shooter, class ACharacter* Target, bool Counter) override;


public:
	void BossDefaultAttack();
	void BossDefaultAttack2();
	void BossSkill1();
	void BossSKill2();

public:
	void SetCharacterGlow(FVector Color, bool GlowEnable);


public:
	void BossAbilityEnd();

public:
	const bool& GetBossAbilityEnable();
	
};
