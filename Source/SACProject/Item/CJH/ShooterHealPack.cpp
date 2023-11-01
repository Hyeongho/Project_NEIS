// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHealPack.h"

AShooterHealPack::AShooterHealPack()
	: Super()
	, m_HealPercent(0.5f)
{
	m_ItemName = TEXT("ShooterHealPack");
	m_ShooterItemType = EShooterItemType::HealPack;
}

void AShooterHealPack::OnFinishItemZCurve()
{
	Destroy();
}
