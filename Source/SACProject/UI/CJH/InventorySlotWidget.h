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
	/* 아이템 습득 시 적용 */
	void SetWeaponIcon(AShooterWeapon* InWeapon);

	/* 무기 장착 시 적용 */
	void SetEquipWeapon();

	/* 무기 장착 해제 시 적용 */
	void SetUnEquipWeapon();

	/* 아이템 버릴 때 적용 */
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
