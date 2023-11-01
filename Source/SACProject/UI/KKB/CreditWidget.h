// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CreditWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UCreditWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCreditWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
