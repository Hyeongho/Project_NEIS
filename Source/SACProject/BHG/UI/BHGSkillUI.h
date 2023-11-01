// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "BHGSkillUI.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UBHGSkillUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	//Default Attack Image
	class UImage*		mDefaultAttackImage;

	//Ability CoolTime
	TObjectPtr<UProgressBar>	mEvadeCoolTimeBar;
	TObjectPtr<UProgressBar>	mShadowCoolTimeBar;
	TObjectPtr<UProgressBar>	mUltimateCoolTimeBar;
	TObjectPtr<UProgressBar>	mCounterCoolTimeBar;
	TObjectPtr<UProgressBar>	mNightmareCoolTimeBar;


	//Ability CoolTimeText
	TObjectPtr<UTextBlock>	mEvadeCoolTimeText;
	TObjectPtr<UTextBlock>	mShadowCoolTimeText;
	TObjectPtr<UTextBlock>	mUltimateCoolTimeText;
	TObjectPtr<UTextBlock>	mCounterCoolTimeText;
	TObjectPtr<UTextBlock>	mNightmareCoolTimeText;

private:
	float		OpacityTime;


public:
	void DefaultAttackImageOpacity();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
