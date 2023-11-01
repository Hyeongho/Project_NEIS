// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterWeapon.h"
#include "ShooterLauncher.generated.h"

class AShooterProjectileBase;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterLauncher : public AShooterWeapon
{
	GENERATED_BODY()

public:
	AShooterLauncher();

protected:
	virtual void SendBullet() override;

protected:
	// 스폰할 유탄 클래스 설정
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterProjectileBase> m_GrenadeProjectileClass;
};
