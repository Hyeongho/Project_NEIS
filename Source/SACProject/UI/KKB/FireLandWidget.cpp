// Fill out your copyright notice in the Description page of Project Settings.


#include "FireLandWidget.h"

UFireLandWidget::UFireLandWidget(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
}

void UFireLandWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UFireLandWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	m_BossHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHP")));

	m_MaxHP = 0.f;
	m_CurHP = 0.f;

	m_BossHP->SetPercent(m_CurHP / m_MaxHP);
}

void UFireLandWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFireLandWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UFireLandWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_BossHP->SetPercent(m_CurHP / m_MaxHP);
}
