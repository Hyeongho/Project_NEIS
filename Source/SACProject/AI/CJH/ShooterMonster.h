// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../AICharacter.h"
#include "BulletHit.h"
#include "ShooterMonster.generated.h"

class UItemDropComponent;
class UParticleSystem;
class USoundCue;
class UAnimMontage;
class UDamageTextWidget;
class AShooterMonsterController;
class AShooterColliderBase;
class AShooterMonsterProjectile;
class AShooterItem;
class AScoreItem;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterMonster : public AAICharacter, public IBulletHit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayHitMontage(FName SectionName, float PlayRate = 1.0f);

	void ResetHitReactTimer();

	void ResetAttackTimer();

	void PlayDeathMontage(float PlayRate = 1.0f);

	void DestroyMonster();

	void DropItem();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsAlive() const;

	void Die();

	void ShowDamageText(int32 Damage, const FVector& HitLocation);

	void ResetStun();

	void PlayAttackMontage(FName SectionName, float PlayRate = 1.0f);

	FName GetAttackSectionName() const;

	void SpawnHitBox();
	void SpawnProjectile();

	/**
	* IBulletHit interface
	*/
public:
	virtual void BulletHit_Implementation(FHitResult HitResult) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UItemDropComponent> m_ItemDropComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem> m_ImpactParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_ImpactSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_HitMontage;

	FTimerHandle m_HitReactTimer;
	float m_HitReactTime;
	bool m_CanHitReact;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool m_Stunned;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	float m_StunChance;

	TObjectPtr<AShooterMonsterController> m_MonsterController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_AttackMontage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TArray<FName> m_AttackSectionNames;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterColliderBase> m_HitBoxClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterMonsterProjectile> m_ProjectileClass;

	bool m_CanAttack;

	FTimerHandle m_AttackTimer;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float m_AttackCoolTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_DeathMontage;

	FTimerHandle m_DeathTimer;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float m_DeathTime;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool m_LongRange;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<AScoreItem> m_ScoreItem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	int32 m_ScorePoint;

public:
	FORCEINLINE bool GetStunned() const { return m_Stunned; }
	FORCEINLINE bool GetCanAttack() const { return m_CanAttack; }
	FORCEINLINE TObjectPtr<UAnimMontage> GetAttackMontage() const { return m_AttackMontage; }

public:
	void SetStunned(bool Stunned);
	void SetCanAttack(bool CanAttack);
};
