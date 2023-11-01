// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/Image.h"
#include "../../Item/CJH/ShooterWeapon.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInventorySlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_WeaponIcon = Cast<UImage>(GetWidgetFromName(TEXT("WeaponIcon")));
	m_WeaponIcon->SetVisibility(ESlateVisibility::Collapsed);
	m_EmptyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EmptyText")));
	m_EmptyText->SetVisibility(ESlateVisibility::Visible);
}

void UInventorySlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventorySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventorySlotWidget::SetWeaponIcon(AShooterWeapon* InWeapon)
{
	if (!IsValid(InWeapon))
		return;

	switch (InWeapon->GetShooterWeaponType())
	{
	case EShooterWeaponType::SubmachineGun:
		if (IsValid(m_SubmachinegunIcon))
		{
			m_WeaponIcon->SetBrushFromMaterial(m_SubmachinegunIcon);
			m_WeaponIcon->SetVisibility(ESlateVisibility::Visible);
			m_EmptyText->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	case EShooterWeaponType::AssaultRifle:
		if (IsValid(m_AssaultRifleIcon))
		{
			m_WeaponIcon->SetBrushFromMaterial(m_AssaultRifleIcon);
			m_WeaponIcon->SetVisibility(ESlateVisibility::Visible);
			m_EmptyText->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	case EShooterWeaponType::Shotgun:
		if (IsValid(m_ShotgunIcon))
		{
			m_WeaponIcon->SetBrushFromMaterial(m_ShotgunIcon);
			m_WeaponIcon->SetVisibility(ESlateVisibility::Visible);
			m_EmptyText->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	case EShooterWeaponType::GrenadeLauncher:
		if (IsValid(m_GrenadeLauncherIcon))
		{
			m_WeaponIcon->SetBrushFromMaterial(m_GrenadeLauncherIcon);
			m_WeaponIcon->SetVisibility(ESlateVisibility::Visible);
			m_EmptyText->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	}
}

void UInventorySlotWidget::SetEquipWeapon()
{
	if (IsValid(EquipWeaponAnim))
		PlayAnimation(EquipWeaponAnim);
}

void UInventorySlotWidget::SetUnEquipWeapon()
{
	if (IsValid(EquipWeaponAnim))
		PlayAnimation(EquipWeaponAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UInventorySlotWidget::SetEmpty()
{
	m_WeaponIcon->SetVisibility(ESlateVisibility::Collapsed);
	m_EmptyText->SetVisibility(ESlateVisibility::Visible);

	if (IsValid(EquipWeaponAnim))
		PlayAnimation(EquipWeaponAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}
