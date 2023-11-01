// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "AmmoDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UAmmoDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAmmoDisplayWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_CurrentAmmoText;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_MagazineAmmoText;

public:
	void SetCurrentAmmo(int32 InCurrentAmmo);
	void SetMagazineAmmo(int32 InMagazineAmmo);
};
