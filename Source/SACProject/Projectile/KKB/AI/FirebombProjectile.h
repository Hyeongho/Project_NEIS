// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Meson_Projectile.h"
#include "FirebombProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AFirebombProjectile : public AMeson_Projectile
{
	GENERATED_BODY()
	
public:
	AFirebombProjectile();

protected:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> m_FirebombProj;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
