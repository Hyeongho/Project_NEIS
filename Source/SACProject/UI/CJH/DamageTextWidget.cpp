// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidget.h"

UDamageTextWidget::UDamageTextWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_DestroyTime(1.5f)
	, m_DestroyTimeAcc(0.0f)
{
}

void UDamageTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//UE_LOG(LogTemp, Warning, TEXT("NativeOnInitialized"));
}

void UDamageTextWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//UE_LOG(LogTemp, Warning, TEXT("NativePreConstruct"));
}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));

	m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HitDamage")));

	m_DestroyTimeAcc = m_DestroyTime;

	if (IsValid(DamageTextAnim))
		PlayAnimation(DamageTextAnim);
}

void UDamageTextWidget::NativeDestruct()
{
	Super::NativeDestruct();

	//UE_LOG(LogTemp, Warning, TEXT("NativeDestruct"));
}

void UDamageTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_DestroyTime <= 0.0f)
		RemoveFromParent();

	m_DestroyTimeAcc -= InDeltaTime;

	float OpacityPercent = m_DestroyTimeAcc / m_DestroyTime;
	SetRenderOpacity(OpacityPercent);

	UpdateLocation();
}

void UDamageTextWidget::UpdateLocation()
{
	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), m_DamageLocation, ScreenPosition);
	SetPositionInViewport(ScreenPosition);
}

void UDamageTextWidget::SetDamageText(int32 Damage, const FVector& HitLocation)
{
	if (IsValid(m_DamageText))
		m_DamageText->SetText(FText::AsNumber(Damage));

	m_DamageLocation = HitLocation;
}
