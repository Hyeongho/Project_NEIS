// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairAmmoWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UCrosshairAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCrosshairAmmoWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void GetMaterial();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_AmmoImage;

	TObjectPtr<UMaterialInstanceDynamic> m_AmmoMaterial;

public:
	void SetAmmo(int32 InAmmoCurrent, int32 InAmmoMax);
	void SetAmmoMax(int32 InAmmoMax);
	void SetAmmoCurrent(int32 InAmmoCurrent);
};
