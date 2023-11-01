// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHpWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../../AI/AICharacter.h"
#include "../../AI/AIState.h"

void UBossHpWidget::SetBarValue(float Value)
{
	mBossHpBar->SetPercent(Value);
}

void UBossHpWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBossHpWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	mBossHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossProgressBar")));

	
}

void UBossHpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBossHpWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBossHpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
