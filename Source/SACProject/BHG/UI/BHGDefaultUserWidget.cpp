// Fill out your copyright notice in the Description page of Project Settings.


#include "BHGDefaultUserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../../Player/PlayerCharacter.h"
#include "../../Player/DefaultPlayerState.h"

void UBHGDefaultUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBHGDefaultUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarHP")));
	mEnergyBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBarEnergy")));
}

void UBHGDefaultUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBHGDefaultUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBHGDefaultUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APlayerCharacter* OwnerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (IsValid(mHPBar) && IsValid(mEnergyBar))
	{
		if (IsValid(OwnerCharacter))
		{
			ADefaultPlayerState* DefaultState = Cast <ADefaultPlayerState>(OwnerCharacter->GetPlayerState());

			if (IsValid(DefaultState))
			{
				int32 CurrentHp = DefaultState->GetHP();
				int32 MaxHp = DefaultState->GetHPMax();

				int32 CurrentEnergy = DefaultState->GetMP();
				int32 MaxEnergy = DefaultState->GetMPMax();

				
				float HpValue = (float)CurrentHp / (float)MaxHp;
				float EnergyValue = (float)CurrentEnergy / (float)MaxEnergy;

				mHPBar->SetPercent(1.0 - HpValue);
				mEnergyBar->SetPercent(1.0 - EnergyValue);
			}
		}
	}
}
