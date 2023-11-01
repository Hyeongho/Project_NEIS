// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterItem.h"
#include "ShooterAmmo.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterAmmo : public AShooterItem
{
	GENERATED_BODY()

public:
	AShooterAmmo();

protected:
	virtual void OnFinishItemZCurve() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ammo Property", meta = (AllowPrivateAccess = true))
	int32 m_Ammo;

public:
	FORCEINLINE int32 GetAmmo() const { return m_Ammo; }
};
