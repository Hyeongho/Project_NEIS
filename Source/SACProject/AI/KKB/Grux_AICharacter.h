// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AICharacter.h"
#include "Grux_AICharacter.generated.h"

class UCoolDownComponent;
class AGrux_EarthquakeBox;
class UDamageTextWidget;
class UFireLandWidget;

UCLASS()
class SACPROJECT_API AGrux_AICharacter : public AAICharacter
{
	GENERATED_BODY()

public:
	AGrux_AICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected: // Stampede Variable
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCoolDownComponent> m_StampedeCooldown;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_StampedeCoolTime;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_StampedeDamage;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_StampedeStunTime;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool	m_IsStun;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector	m_StampedeTargetPoint;


protected: // Earthquake Variable
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCoolDownComponent> m_EarthquakeCooldown;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_EarthquakeCoolTime;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_EarthquakeDamage;

	TObjectPtr<AGrux_EarthquakeBox> m_EarthquakeBox;


private:
	bool	m_TraceStampedeTarget;
	bool	m_IsRun;
	float	m_TraceMaxTime;
	float	m_TraceCurTime;
	float	m_RunSpeed;
	float	m_StunCurTime;

	bool	m_IsBerserk;

	TObjectPtr<UFireLandWidget> m_FireLandWidget;

protected: // Widget
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UIWidget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;

public:
	inline bool IsTraceStampedeTarget() const { return m_TraceStampedeTarget; }
	inline bool IsBerserk() const { return m_IsBerserk; }
	bool IsStampedeActive() const;
	bool IsEarthquakeActive() const;
	inline bool IsStun() const { return m_IsStun; }
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

public:
	void SetStun();
	void StartStampedeCooldown();

public:
	void TraceTarget() { m_TraceStampedeTarget = true; }
	void SetStampedeTarget(const FVector& TargetPoint);


public:
	void Attack();
	void Attack_Active();
	void Skill1_DoublePain();
	void Skill1_DoublePain_ActiveSkill();
	void Skill2_Stampede_Ready();
	void Skill2_Stampede_Run();
	void Skill2_Stampede_Attack();
	void Skill2_Stampede_Attack_ActiveSkill();
	void Skill2_Stampede_Stun();
	void Skill3_Earthquake();
	void Skill3_Earthquake_ActiveSkill();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
