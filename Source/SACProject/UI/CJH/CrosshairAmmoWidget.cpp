// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairAmmoWidget.h"
#include "Components/Image.h"
#include "../../Player/CJH/ShooterCharacter.h"

UCrosshairAmmoWidget::UCrosshairAmmoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCrosshairAmmoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCrosshairAmmoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCrosshairAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_AmmoImage = Cast<UImage>(GetWidgetFromName(TEXT("Ammo")));
	
	GetMaterial();
}

void UCrosshairAmmoWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCrosshairAmmoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCrosshairAmmoWidget::GetMaterial()
{
	UMaterialInstanceDynamic* DynamicMaterial = m_AmmoImage->GetDynamicMaterial();
	if (IsValid(DynamicMaterial))
	{
		m_AmmoMaterial = DynamicMaterial;
	}
}

void UCrosshairAmmoWidget::SetAmmo(int32 InAmmoCurrent, int32 InAmmoMax)
{
	if (IsValid(m_AmmoMaterial))
	{
		m_AmmoMaterial->SetScalarParameterValue(TEXT("Rounds_Current"), static_cast<float>(InAmmoCurrent));
		m_AmmoMaterial->SetScalarParameterValue(TEXT("Rounds_Max"), static_cast<float>(InAmmoMax));
	}
}

void UCrosshairAmmoWidget::SetAmmoMax(int32 InAmmoMax)
{
	if (IsValid(m_AmmoMaterial))
	{
		m_AmmoMaterial->SetScalarParameterValue(TEXT("Rounds_Max"), static_cast<float>(InAmmoMax));
	}
}

void UCrosshairAmmoWidget::SetAmmoCurrent(int32 InAmmoCurrent)
{
	if (IsValid(m_AmmoMaterial))
	{
		m_AmmoMaterial->SetScalarParameterValue(TEXT("Rounds_Current"), static_cast<float>(InAmmoCurrent));
	}
}
