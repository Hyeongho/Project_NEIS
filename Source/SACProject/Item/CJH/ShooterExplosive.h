// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../DefaultItem.h"
#include "../../AI/CJH/BulletHit.h"
#include "ShooterExplosive.generated.h"

class AShooterColliderBase;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterExplosive : public ADefaultItem, public IBulletHit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterExplosive();

	/**
	* IBulletHit interface
	*/
public:
	virtual void BulletHit_Implementation(FHitResult HitResult) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem> m_ExplosionParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_ExplosionSound;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Explosion", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterColliderBase> m_HitBoxClass;
};
