// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "../../Player/CJH/ShooterCharacter.h"

UCrosshairWidget::UCrosshairWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_TopPosition(FVector2D(0.0f))
	, m_BottomPosition(FVector2D(0.0f))
	, m_LeftPosition(FVector2D(0.0f))
	, m_RightPosition(FVector2D(0.0f))
	, m_CrosshairMuliplier(0.0f)
	, m_CrosshairSpreadMax(8.0f)
{
}

void UCrosshairWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCrosshairWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CrosshairTop = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairTop")));
	m_CrosshairBottom = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairBottom")));
	m_CrosshairLeft = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairLeft")));
	m_CrosshairRight = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairRight")));
	m_CrosshairDot = Cast<UImage>(GetWidgetFromName(TEXT("CrosshairDot")));

	m_TopPosition = m_CrosshairTop->GetRenderTransform().Translation;
	m_BottomPosition = m_CrosshairBottom->GetRenderTransform().Translation;
	m_LeftPosition = m_CrosshairLeft->GetRenderTransform().Translation;
	m_RightPosition = m_CrosshairRight->GetRenderTransform().Translation;
}

void UCrosshairWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCrosshairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsValid(m_OwnerCharacter))
	{
		m_CrosshairMuliplier = m_OwnerCharacter->GetCrosshairSpreadMultiplier();

		FVector2D TopPosition = m_TopPosition;
		TopPosition.Y -= m_CrosshairMuliplier * m_CrosshairSpreadMax;
		m_CrosshairTop->SetRenderTranslation(TopPosition);

		FVector2D BottomPosition = m_BottomPosition;
		BottomPosition.Y += m_CrosshairMuliplier * m_CrosshairSpreadMax;
		m_CrosshairBottom->SetRenderTranslation(BottomPosition);

		FVector2D LeftPosition = m_LeftPosition;
		LeftPosition.X -= m_CrosshairMuliplier * m_CrosshairSpreadMax;
		m_CrosshairLeft->SetRenderTranslation(LeftPosition);

		FVector2D RightPosition = m_RightPosition;
		RightPosition.X += m_CrosshairMuliplier * m_CrosshairSpreadMax;
		m_CrosshairRight->SetRenderTranslation(RightPosition);
	}
	else
	{
		m_OwnerCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
}

void UCrosshairWidget::SetOwnerCharacter(AShooterCharacter* InCharacter)
{
	m_OwnerCharacter = InCharacter;
}
