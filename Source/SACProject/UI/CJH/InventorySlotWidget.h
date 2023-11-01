// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class AShooterWeapon;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	/* ������ ���� �� ���� */
	void SetWeaponIcon(AShooterWeapon* InWeapon);

	/* ���� ���� �� ���� */
	void SetEquipWeapon();

	/* ���� ���� ���� �� ���� */
	void SetUnEquipWeapon();

	/* ������ ���� �� ���� */
	void SetEmpty();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_WeaponIcon;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* EquipWeaponAnim;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_EmptyText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> m_SubmachinegunIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> m_AssaultRifleIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> m_ShotgunIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInstance> m_GrenadeLauncherIcon;
};
