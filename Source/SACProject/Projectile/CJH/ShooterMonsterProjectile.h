// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterProjectileBase.h"
#include "../../AI/CJH/BulletHit.h"
#include "ShooterMonsterProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterMonsterProjectile : public AShooterProjectileBase, public IBulletHit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterMonsterProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateToTarget();

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LockOn();

	/**
	* IBulletHit interface
	*/
public:
	virtual void BulletHit_Implementation(FHitResult HitResult) override;

protected:
	TObjectPtr<AActor> m_Target;
	FVector m_InitialTargetLocation;

	bool m_LockOn;

	FTimerHandle m_LockOnTimer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float m_LockOnTime;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	int32 m_Damage;

public:
	void SetTarget(AActor* InTarget);
};
