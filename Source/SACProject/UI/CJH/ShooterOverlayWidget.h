// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ShooterOverlayWidget.generated.h"

class UCrosshairAmmoWidget;
class UAmmoDisplayWidget;
class UInventorySlotWidget;
class UShooterScoreWidget;
class AShooterWeapon;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UShooterOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UShooterOverlayWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetCrosshairAmmo(int32 InAmmoCurrent, int32 InAmmoMax);
	void SetCrosshairAmmoCurrent(int32 InAmmoCurrent);
	void SetCrosshairAmmoMax(int32 InAmmoMax);

	void SetDisplayAmmoCurrent(int32 InCurrentAmmo);
	void SetDisplayAmmoMagazine(int32 InMagazineAmmo);

	void SetSlotWeapon(AShooterWeapon* InWeapon, int32 SlotIndex);
	void SetSlotEquipWeapon(int32 SlotIndex);
	void SetSlotUnEquipWeapon(int32 SlotIndex);
	void SetSlotEmpty(int32 SlotIndex);

	void SetSlot1Weapon(AShooterWeapon* InWeapon);
	void SetSlot1EquipWeapon();
	void SetSlot1UnEquipWeapon();
	void SetSlot1Empty();

	void SetSlot2Weapon(AShooterWeapon* InWeapon);
	void SetSlot2EquipWeapon();
	void SetSlot2UnEquipWeapon();
	void SetSlot2Empty();

	void SetSlot3Weapon(AShooterWeapon* InWeapon);
	void SetSlot3EquipWeapon();
	void SetSlot3UnEquipWeapon();
	void SetSlot3Empty();

	void SetSlot4Weapon(AShooterWeapon* InWeapon);
	void SetSlot4EquipWeapon();
	void SetSlot4UnEquipWeapon();
	void SetSlot4Empty();

	void SetCurrentScoreText(int32 Score);
	void PlayCurrentScoreAnim();
	void SetMaxScoreText(int32 Score);

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCrosshairAmmoWidget> m_CrosshairAmmo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAmmoDisplayWidget> m_AmmoDisplay;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInventorySlotWidget> m_Slot1;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInventorySlotWidget> m_Slot2;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInventorySlotWidget> m_Slot3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInventorySlotWidget> m_Slot4;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UShooterScoreWidget> m_ShooterScore;
};
