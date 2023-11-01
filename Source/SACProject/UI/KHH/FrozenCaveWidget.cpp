// Fill out your copyright notice in the Description page of Project Settings.


#include "FrozenCaveWidget.h"


UFrozenCaveWidget::UFrozenCaveWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFrozenCaveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UFrozenCaveWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	m_BossHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHP")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarHp")));
	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarEnergy")));

	m_BossMaxHP = 0.f;
	m_BossCurHP = 0.f;

	m_BossHP->SetPercent(m_BossCurHP / m_BossMaxHP);
}

void UFrozenCaveWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFrozenCaveWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UFrozenCaveWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_BossHP->SetPercent(m_BossCurHP / m_BossMaxHP);
	m_HPBar->SetPercent(m_PlayerCurHP / m_PlayerMaxHP);
	m_MPBar->SetPercent(m_PlayerCurMP / m_PlayerMaxMP);
}
