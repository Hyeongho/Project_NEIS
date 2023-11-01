// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileBase.h"
#include "BossRockProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABossRockProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	ABossRockProjectile();

protected:
	UPROPERTY(Category = "StaticMesh", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>		m_Static;

	UPROPERTY(Category = "Meteo", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystemComponent>	m_MeteoEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ProjectileFire(FVector Velocity, class ACharacter* Shooter);

protected:
		virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

		virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
