// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAmmo.h"

AShooterAmmo::AShooterAmmo()
	: Super()
	, m_Ammo(50)
{
	m_ItemName = TEXT("ShooterAmmo");
	m_ShooterItemType = EShooterItemType::Ammo;
}

void AShooterAmmo::OnFinishItemZCurve()
{
	Destroy();
}
