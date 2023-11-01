// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHpWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../../AI/AICharacter.h"
#include "../../AI/AIState.h"

void UMonsterHpWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMonsterHpWidget::NativePreConstruct()
{
	Super::NativeConstruct();

	mMonsterHpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterBar")));
	mMonsterHpBar->SetPercent(1.f);

}

void UMonsterHpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMonsterHpWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMonsterHpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
