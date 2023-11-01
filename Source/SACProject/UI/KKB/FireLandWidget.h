// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "FireLandWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UFireLandWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFireLandWidget(const FObjectInitializer& ObjectInitializer);

private:
	UProgressBar* m_BossHP;

	float m_MaxHP;
	float m_CurHP;

public:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetMaxHP(float HP) { m_MaxHP = HP; }
	void SetCurHP(float HP) { m_CurHP = HP; }

	inline float GetMaxHP() const { return m_MaxHP; }
	inline float GetCurHP() const { return m_CurHP; }
	
};
