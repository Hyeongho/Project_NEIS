// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterItem.h"
#include "ShooterHealPack.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterHealPack : public AShooterItem
{
	GENERATED_BODY()

public:
	AShooterHealPack();

protected:
	virtual void OnFinishItemZCurve() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	float m_HealPercent;

public:
	FORCEINLINE float GetHealPercent() const { return m_HealPercent; }
};
