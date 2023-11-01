// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacter.h"
#include "Kwang_PlayerCharacter.generated.h"

class UCoolDownComponent;
class UKwang_UserWidget;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AKwang_PlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AKwang_PlayerCharacter();

private: // Action CoolTime Component
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCoolDownComponent> m_DashCooldown;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCoolDownComponent> m_ThunderStormCooldown;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCoolDownComponent> m_ThunderAuraCooldown;

private: // Charge Variable
	int32			m_ChargeRate;

private: // Aura Variable
	FTimerHandle	m_AuraLifeTimerHnd;
	float			m_AuraLifeTime;
	float			m_AuraCooldownTime;

	FTimerHandle	m_AuraEnhanceTimerHnd;
	bool			m_AuraActive;
	int32			m_AuraSkillCount;
	int32			m_AuraSkillMax;

	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> m_AuraEffect;

private: // Dash Variable
	float			m_DashCooldownTime;
	float			m_DashDistance;

private:
	TObjectPtr<UKwang_UserWidget> m_PlayerWidget;


public:
	bool IsAuraEnhanced() { return m_AuraActive; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AddSkill1Charge();

public: // Action
	void Attack();
	void Attack_Enhance();
	void Dash();
	void Skill1_ChargeShot();
	void Skill1_ChargeShot_ActiveSkill();
	void Skill2_ThunderStorm();
	void Skill2_ThunderStorm_ActiveSkill();
	void Skill2_ThunderStorm_ActiveSkill_Enhance();
	void Skill3_ThunderAura();
	void Skill3_ThunderAura_ActiveSkill();

private:
	void Skill3_AuraEnd();
	void ShootProjectile();

public:
	UFUNCTION(BlueprintCallable)
	void HidePlayerWidget();

	UFUNCTION(BlueprintCallable)
	void VisiblePlayerWidget();
};
