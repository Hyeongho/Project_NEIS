// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "GrenadeProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class USoundCue;
class AShooterColliderBase;

UCLASS()
class SACPROJECT_API AGrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenadeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Shot();

	void FinishShot();

	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> m_CollisionSphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> m_GrenadeMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> m_GrenadeMovement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystemComponent> m_SmokeTrail;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Smoke", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_SmokeTrailParticle;

	FTimerHandle m_ExplosionTimer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion", meta = (AllowPrivateAccess = true))
	float m_ExplosionTime;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_ExplosionParticle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_ExplosionSound;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bounce", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_BounceSound;

	int32 m_BounceCount;
	const int32 m_BounceCountMax = 5;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterColliderBase> m_HitBoxClass;
};
