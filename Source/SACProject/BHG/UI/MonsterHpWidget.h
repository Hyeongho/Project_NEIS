// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UMonsterHpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UProgressBar>	mMonsterHpBar;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
