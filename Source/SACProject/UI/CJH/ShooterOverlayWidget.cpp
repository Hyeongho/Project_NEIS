// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterOverlayWidget.h"
#include "CrosshairAmmoWidget.h"
#include "AmmoDisplayWidget.h"
#include "InventorySlotWidget.h"
#include "ShooterScoreWidget.h"

UShooterOverlayWidget::UShooterOverlayWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UShooterOverlayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UShooterOverlayWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UShooterOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CrosshairAmmo = Cast<UCrosshairAmmoWidget>(GetWidgetFromName(TEXT("CrosshairAmmo")));
	m_AmmoDisplay = Cast<UAmmoDisplayWidget>(GetWidgetFromName(TEXT("AmmoDisplay")));
	m_Slot1 = Cast<UInventorySlotWidget>(GetWidgetFromName(TEXT("Slot1")));
	m_Slot2 = Cast<UInventorySlotWidget>(GetWidgetFromName(TEXT("Slot2")));
	m_Slot3 = Cast<UInventorySlotWidget>(GetWidgetFromName(TEXT("Slot3")));
	m_Slot4 = Cast<UInventorySlotWidget>(GetWidgetFromName(TEXT("Slot4")));
	m_ShooterScore = Cast<UShooterScoreWidget>(GetWidgetFromName(TEXT("ShooterScore")));
}

void UShooterOverlayWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UShooterOverlayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UShooterOverlayWidget::SetCrosshairAmmo(int32 InAmmoCurrent, int32 InAmmoMax)
{
	if (IsValid(m_CrosshairAmmo))
		m_CrosshairAmmo->SetAmmo(InAmmoCurrent, InAmmoMax);
}

void UShooterOverlayWidget::SetCrosshairAmmoCurrent(int32 InAmmoCurrent)
{
	if (IsValid(m_CrosshairAmmo))
		m_CrosshairAmmo->SetAmmoCurrent(InAmmoCurrent);
}

void UShooterOverlayWidget::SetCrosshairAmmoMax(int32 InAmmoMax)
{
	if (IsValid(m_CrosshairAmmo))
		m_CrosshairAmmo->SetAmmoMax(InAmmoMax);
}

void UShooterOverlayWidget::SetDisplayAmmoCurrent(int32 InCurrentAmmo)
{
	if (IsValid(m_AmmoDisplay))
		m_AmmoDisplay->SetCurrentAmmo(InCurrentAmmo);
}

void UShooterOverlayWidget::SetDisplayAmmoMagazine(int32 InMagazineAmmo)
{
	if (IsValid(m_AmmoDisplay))
		m_AmmoDisplay->SetMagazineAmmo(InMagazineAmmo);
}

void UShooterOverlayWidget::SetSlotWeapon(AShooterWeapon* InWeapon, int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= 4)
		return;

	switch (SlotIndex)
	{
	case 0:
		SetSlot1Weapon(InWeapon);
		break;
	case 1:
		SetSlot2Weapon(InWeapon);
		break;
	case 2:
		SetSlot3Weapon(InWeapon);
		break;
	case 3:
		SetSlot4Weapon(InWeapon);
		break;
	}
}

void UShooterOverlayWidget::SetSlotEquipWeapon(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= 4)
		return;

	switch (SlotIndex)
	{
	case 0:
		SetSlot1EquipWeapon();
		break;
	case 1:
		SetSlot2EquipWeapon();
		break;
	case 2:
		SetSlot3EquipWeapon();
		break;
	case 3:
		SetSlot4EquipWeapon();
		break;
	}
}

void UShooterOverlayWidget::SetSlotUnEquipWeapon(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= 4)
		return;

	switch (SlotIndex)
	{
	case 0:
		SetSlot1UnEquipWeapon();
		break;
	case 1:
		SetSlot2UnEquipWeapon();
		break;
	case 2:
		SetSlot3UnEquipWeapon();
		break;
	case 3:
		SetSlot4UnEquipWeapon();
		break;
	}
}

void UShooterOverlayWidget::SetSlotEmpty(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= 4)
		return;

	switch (SlotIndex)
	{
	case 0:
		SetSlot1Empty();
		break;
	case 1:
		SetSlot2Empty();
		break;
	case 2:
		SetSlot3Empty();
		break;
	case 3:
		SetSlot4Empty();
		break;
	}
}

void UShooterOverlayWidget::SetSlot1Weapon(AShooterWeapon* InWeapon)
{
	if (IsValid(m_Slot1))
		m_Slot1->SetWeaponIcon(InWeapon);
}

void UShooterOverlayWidget::SetSlot1EquipWeapon()
{
	if (IsValid(m_Slot1))
		m_Slot1->SetEquipWeapon();
}

void UShooterOverlayWidget::SetSlot1UnEquipWeapon()
{
	if (IsValid(m_Slot1))
		m_Slot1->SetUnEquipWeapon();
}

void UShooterOverlayWidget::SetSlot1Empty()
{
	if (IsValid(m_Slot1))
		m_Slot1->SetEmpty();
}

void UShooterOverlayWidget::SetSlot2Weapon(AShooterWeapon* InWeapon)
{
	if (IsValid(m_Slot2))
		m_Slot2->SetWeaponIcon(InWeapon);
}

void UShooterOverlayWidget::SetSlot2EquipWeapon()
{
	if (IsValid(m_Slot2))
		m_Slot2->SetEquipWeapon();
}

void UShooterOverlayWidget::SetSlot2UnEquipWeapon()
{
	if (IsValid(m_Slot2))
		m_Slot2->SetUnEquipWeapon();
}

void UShooterOverlayWidget::SetSlot2Empty()
{
	if (IsValid(m_Slot2))
		m_Slot2->SetEmpty();
}

void UShooterOverlayWidget::SetSlot3Weapon(AShooterWeapon* InWeapon)
{
	if (IsValid(m_Slot3))
		m_Slot3->SetWeaponIcon(InWeapon);
}

void UShooterOverlayWidget::SetSlot3EquipWeapon()
{
	if (IsValid(m_Slot3))
		m_Slot3->SetEquipWeapon();
}

void UShooterOverlayWidget::SetSlot3UnEquipWeapon()
{
	if (IsValid(m_Slot3))
		m_Slot3->SetUnEquipWeapon();
}

void UShooterOverlayWidget::SetSlot3Empty()
{
	if (IsValid(m_Slot3))
		m_Slot3->SetEmpty();
}

void UShooterOverlayWidget::SetSlot4Weapon(AShooterWeapon* InWeapon)
{
	if (IsValid(m_Slot4))
		m_Slot4->SetWeaponIcon(InWeapon);
}

void UShooterOverlayWidget::SetSlot4EquipWeapon()
{
	if (IsValid(m_Slot4))
		m_Slot4->SetEquipWeapon();
}

void UShooterOverlayWidget::SetSlot4UnEquipWeapon()
{
	if (IsValid(m_Slot4))
		m_Slot4->SetUnEquipWeapon();
}

void UShooterOverlayWidget::SetSlot4Empty()
{
	if (IsValid(m_Slot4))
		m_Slot4->SetEmpty();
}

void UShooterOverlayWidget::SetCurrentScoreText(int32 Score)
{
	if (IsValid(m_ShooterScore))
		m_ShooterScore->SetCurrentScoreText(Score);
}

void UShooterOverlayWidget::PlayCurrentScoreAnim()
{
	if (IsValid(m_ShooterScore))
		m_ShooterScore->PlayCurrentScoreAnim();
}

void UShooterOverlayWidget::SetMaxScoreText(int32 Score)
{
	if (IsValid(m_ShooterScore))
		m_ShooterScore->SetMaxScoreText(Score);
}
