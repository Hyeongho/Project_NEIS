// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoDisplayWidget.h"

UAmmoDisplayWidget::UAmmoDisplayWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAmmoDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UAmmoDisplayWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UAmmoDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CurrentAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentAmmo")));
	m_MagazineAmmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagazineAmmo")));
}

void UAmmoDisplayWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UAmmoDisplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UAmmoDisplayWidget::SetCurrentAmmo(int32 InCurrentAmmo)
{
	if (IsValid(m_CurrentAmmoText))
		m_CurrentAmmoText->SetText(FText::AsNumber(InCurrentAmmo));
}

void UAmmoDisplayWidget::SetMagazineAmmo(int32 InMagazineAmmo)
{
	if (IsValid(m_MagazineAmmoText))
		m_MagazineAmmoText->SetText(FText::AsNumber(InMagazineAmmo));
}
