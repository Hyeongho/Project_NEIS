// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "BossHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBossHpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UProgressBar>	mBossHpBar;

public:
	void SetBarValue(float Value);
	

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
