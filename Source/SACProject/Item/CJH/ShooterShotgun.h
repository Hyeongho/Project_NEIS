// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterWeapon.h"
#include "ShooterShotgun.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterShotgun : public AShooterWeapon
{
	GENERATED_BODY()

public:
	AShooterShotgun();

protected:
	virtual void SendBullet() override;
};
