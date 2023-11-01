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
	// ������ ��ź Ŭ���� ����
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterProjectileBase> m_GrenadeProjectileClass;
};
