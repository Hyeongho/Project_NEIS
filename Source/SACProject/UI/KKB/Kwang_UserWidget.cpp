// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"

UKwang_UserWidget::UKwang_UserWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UKwang_UserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UKwang_UserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	
	m_QCooltimeText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("QCooltimeText")));

	if (IsValid(m_QCooltimeText))
		m_QCooltimeText->SetVisibility(ESlateVisibility::Hidden);

	m_ECooltimeText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ECooltimeText")));

	if (IsValid(m_ECooltimeText))
		m_ECooltimeText->SetVisibility(ESlateVisibility::Hidden);

	m_SpaceCooltimeText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("SpaceCooltimeText")));

	if (IsValid(m_SpaceCooltimeText))
		m_SpaceCooltimeText->SetVisibility(ESlateVisibility::Hidden);

	
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	
	m_EBuffImage = Cast<UImage>(GetWidgetFromName(TEXT("EBuffImage")));

	if (IsValid(m_EBuffImage))
		m_EBuffImage->SetVisibility(ESlateVisibility::Hidden);

	m_EBuffText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EBuffText")));

	if (IsValid(m_EBuffText))
		m_EBuffText->SetVisibility(ESlateVisibility::Hidden);

	m_EBuffRemainTime = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EBuffRemainTime")));

	if (IsValid(m_EBuffRemainTime))
		m_EBuffRemainTime->SetVisibility(ESlateVisibility::Hidden);
}

void UKwang_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UKwang_UserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UKwang_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UKwang_UserWidget::HiddenAll()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UKwang_UserWidget::VisibleAll()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UKwang_UserWidget::SetQRemainCoolTime(float Remain)
{
	if (!IsValid(m_QCooltimeText))
		return;

	if (Remain <= 0.f) {
		m_QCooltimeText->SetVisibility(ESlateVisibility::Hidden);

		return;
	}

	FString str = FString::Printf(TEXT("%d"), (int32)Remain);
	FText txt = FText::FromString(str);

	m_QCooltimeText->SetVisibility(ESlateVisibility::Visible);
	m_QCooltimeText->SetText(txt);
}

void UKwang_UserWidget::SetERemainCoolTime(float Remain)
{
	if (!IsValid(m_ECooltimeText))
		return;

	if (Remain <= 0.f) {
		m_ECooltimeText->SetVisibility(ESlateVisibility::Hidden);

		return;
	}

	FString str = FString::Printf(TEXT("%d"), (int32)Remain);
	FText txt = FText::FromString(str);

	m_ECooltimeText->SetVisibility(ESlateVisibility::Visible);
	m_ECooltimeText->SetText(txt);
}

void UKwang_UserWidget::SetSpaceRemainCoolTime(float Remain)
{
	if (!IsValid(m_SpaceCooltimeText)) 
		return;

	if (Remain <= 0.f) {
		m_SpaceCooltimeText->SetVisibility(ESlateVisibility::Hidden);

		return;
	}

	FString str = FString::Printf(TEXT("%d"), (int32)Remain);
	FText txt = FText::FromString(str);

	m_SpaceCooltimeText->SetVisibility(ESlateVisibility::Visible);
	m_SpaceCooltimeText->SetText(txt);
}

void UKwang_UserWidget::SetESkillRemain(float Remain)
{
	if (!IsValid(m_EBuffRemainTime))
		return;


	FString str = FString::Printf(TEXT("%d"), (int32)Remain);
	FText txt = FText::FromString(str);

	m_EBuffRemainTime->SetVisibility(ESlateVisibility::Visible);
	m_EBuffRemainTime->SetText(txt);

}

void UKwang_UserWidget::SetHpRemain(float Remain)
{
	if (IsValid(m_HPBar))
		m_HPBar->SetPercent(Remain);
}

void UKwang_UserWidget::SetEBuffRemain(int32 Remain)
{
	if (IsValid(m_EBuffImage)) 
		m_EBuffImage->SetVisibility(ESlateVisibility::Visible);


	if (IsValid(m_EBuffText)) {
		FString str = FString::Printf(TEXT("%d"), Remain);
		FText txt = FText::FromString(str);

		m_EBuffText->SetVisibility(ESlateVisibility::Visible);
		m_EBuffText->SetText(txt);
	}

	if (Remain <= 0) {
		if (IsValid(m_EBuffImage))
			m_EBuffImage->SetVisibility(ESlateVisibility::Hidden);

		if (IsValid(m_EBuffText))
			m_EBuffText->SetVisibility(ESlateVisibility::Hidden);

		if (IsValid(m_EBuffRemainTime))
			m_EBuffRemainTime->SetVisibility(ESlateVisibility::Hidden);
	}

}
