// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Kwang_UserWidget.generated.h"

class UEditableTextBox;
class UImage;
class UProgressBar;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UKwang_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UKwang_UserWidget(const FObjectInitializer& ObjectInitializer);

protected: // Skill CoolTime
	TObjectPtr<UEditableTextBox>	m_QCooltimeText;
	TObjectPtr<UEditableTextBox>	m_ECooltimeText;
	TObjectPtr<UEditableTextBox>	m_SpaceCooltimeText;

protected: // HP Bar
	TObjectPtr<UProgressBar>	m_HPBar;

protected: // Buff 
	TObjectPtr<UImage>				m_EBuffImage;
	TObjectPtr<UEditableTextBox>	m_EBuffText;
	TObjectPtr<UEditableTextBox>	m_EBuffRemainTime;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void HiddenAll();
	void VisibleAll();
	
public:
	void SetQRemainCoolTime(float Remain);
	void SetERemainCoolTime(float Remain);
	void SetSpaceRemainCoolTime(float Remain);
	void SetESkillRemain(float Remain);
	
	void SetHpRemain(float Remain);

	void SetEBuffRemain(int32 Remain);
};
