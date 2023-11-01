// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "FrozenCaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UFrozenCaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFrozenCaveWidget(const FObjectInitializer& ObjectInitializer);

private:
	TObjectPtr<UProgressBar> m_BossHP;

	TObjectPtr<UProgressBar> m_HPBar;
	TObjectPtr<UProgressBar> m_MPBar;

	float m_BossMaxHP;
	float m_BossCurHP;

	float m_PlayerMaxHP;
	float m_PlayerCurHP;

	float m_PlayerMaxMP;
	float m_PlayerCurMP;

public:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetMaxHP(float HP)
	{
		m_BossMaxHP = HP;
	}

	float GetMaxHP() const
	{
		return m_BossMaxHP;
	}

	void SetCurHP(float HP)
	{
		m_BossCurHP = HP;
	}

	float GetCurHP() const
	{
		return m_BossCurHP;
	}

	void SetPlayerMaxHP(float HP)
	{
		m_PlayerMaxHP = HP;
	}

	float GetPlayerMaxHP() const
	{
		return m_PlayerMaxHP;
	}

	void SetPlayerCurHP(float HP)
	{
		m_PlayerCurHP = HP;
	}

	float GetPlayerCurHP() const
	{
		return m_PlayerCurHP;
	}

	void SetPlayerMaxMP(float MP)
	{
		m_PlayerMaxMP = MP;
	}

	float GetPlayerMaxMP() const
	{
		return m_PlayerMaxMP;
	}

	void SetPlayerCurMP(float MP)
	{
		m_PlayerCurMP = MP;
	}

	float GetPlayerCurMP() const
	{
		return m_PlayerCurMP;
	}
};
