// Fill out your copyright notice in the Description page of Project Settings.


#include "BHGSkillUI.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Player/BHG_Player.h"
#include "../Component/AbilityComponent.h"
#include "../../Player/DefaultPlayerState.h"
#include "../Ability/DefaultAbility.h"

void UBHGSkillUI::DefaultAttackImageOpacity()
{
	mDefaultAttackImage->SetOpacity(0.3f);
}

void UBHGSkillUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBHGSkillUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	mEvadeCoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EvadeBar")));
	mShadowCoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ShadowBar")));
	mUltimateCoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("UltimateBar")));
	mCounterCoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CounterBar")));
	mNightmareCoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("NightmareBar")));

	mEvadeCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EvadeText")));
	mShadowCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ShadowText")));
	mUltimateCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("UltimateText")));
	mCounterCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CounterText")));
	mNightmareCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NightmareText")));

	mDefaultAttackImage = Cast<UImage>(GetWidgetFromName(TEXT("DefaultAttackImage")));

	OpacityTime = 0.f;

}

void UBHGSkillUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBHGSkillUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBHGSkillUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	OpacityTime += InDeltaTime;

	if (OpacityTime > 0.1f)
	{
		mDefaultAttackImage->SetOpacity(mDefaultAttackImage->GetRenderOpacity());
		OpacityTime = 0.f;
	}

	//if(IsValid(mDefaultAttackImage))
	//	mDefaultAttackImage->SetOpacity(mDefaultAttackImage->GetRenderOpacity());


	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (IsValid(mEvadeCoolTimeBar) && IsValid(mShadowCoolTimeBar) && IsValid(mUltimateCoolTimeBar) && IsValid(mCounterCoolTimeBar) &&
		IsValid(mEvadeCoolTimeText) && IsValid(mShadowCoolTimeText) && IsValid(mUltimateCoolTimeText) && IsValid(mCounterCoolTimeText) &&
		IsValid(mNightmareCoolTimeBar) && IsValid(mNightmareCoolTimeText))
	{
	

		if (IsValid(OwnerCharacter))
		{
			//플레이어의 어빌리티컴포넌트로부터 각 어빌리티의 쿨타임을 가져온다. 
			UAbilityComponent* AbilityComp = OwnerCharacter->GetComponentByClass<UAbilityComponent>();

			if (IsValid(AbilityComp))
			{
				float EvadeOriginTime = AbilityComp->FindAbility(TEXT("Evade"))->GetOriginCoolTime();
				float ShadowOriginTime = AbilityComp->FindAbility(TEXT("ShadowPartner"))->GetOriginCoolTime();
				float UltimateOriginTime = AbilityComp->FindAbility(TEXT("Ultimate"))->GetOriginCoolTime();
				float CounterOriginTime = AbilityComp->FindAbility(TEXT("CounterAttack"))->GetOriginCoolTime();
				float NightmareOriginTime = AbilityComp->FindAbility(TEXT("Nightmare"))->GetOriginCoolTime();


				float EvadeCoolTime = AbilityComp->FindAbility(TEXT("Evade"))->GetAbilityCoolTime();
				float ShadowCoolTime = AbilityComp->FindAbility(TEXT("ShadowPartner"))->GetAbilityCoolTime();
				float UltimateCoolTime = AbilityComp->FindAbility(TEXT("Ultimate"))->GetAbilityCoolTime();
				float CounterCoolTime = AbilityComp->FindAbility(TEXT("CounterAttack"))->GetAbilityCoolTime();
				float NightmareCoolTime = AbilityComp->FindAbility(TEXT("Nightmare"))->GetAbilityCoolTime();

				mEvadeCoolTimeBar->SetPercent(EvadeCoolTime / EvadeOriginTime);
				mShadowCoolTimeBar->SetPercent(ShadowCoolTime / ShadowOriginTime);
				mUltimateCoolTimeBar->SetPercent(UltimateCoolTime / UltimateOriginTime);
				mCounterCoolTimeBar->SetPercent(CounterCoolTime / CounterOriginTime);
				mNightmareCoolTimeBar->SetPercent(NightmareCoolTime / NightmareOriginTime);

				//남은 쿨타임을 정수로 변환한다. 
				int32 EvadeCoolTimeInt = FMath::TruncToInt(EvadeCoolTime);
				int32 ShadowCoolTimeInt = FMath::TruncToInt(ShadowCoolTime);
				int32 UltimateCoolTimeInt = FMath::TruncToInt(UltimateCoolTime);
				int32 CounterCoolTimeInt = FMath::TruncToInt(CounterCoolTime);
				int32 NightmareCoolTimeInt = FMath::TruncToInt(NightmareCoolTime);

				//정수로 변환된 쿨타임을 텍스트로 변환한다. 
				FString EvadeCoolTimeText = FString::FromInt(EvadeCoolTimeInt);
				FString ShadowCoolTimeText = FString::FromInt(ShadowCoolTimeInt);
				FString UltimateCoolTimeText = FString::FromInt(UltimateCoolTimeInt);
				FString CounterCoolTimeText = FString::FromInt(CounterCoolTimeInt);
				FString NightmareCoolTimeText = FString::FromInt(NightmareCoolTimeInt);		
				

				//만약 0이라면 숫자를 출력하지 않는다. 
				if (EvadeCoolTime == 0.f)
					mEvadeCoolTimeText->SetText(FText::FromString(""));
				
				// 이전숫자와 다를경우에만 숫자를 교체한다.
				else if (EvadeCoolTimeText != mEvadeCoolTimeText->GetText().ToString())
				{
					FString ZeroString = "0";

					if(EvadeCoolTimeText == ZeroString)
						EvadeCoolTimeText = FString::FromInt(++EvadeCoolTimeInt);

					mEvadeCoolTimeText->SetText(FText::FromString(EvadeCoolTimeText));
				}

				if (ShadowCoolTime == 0.f)
					mShadowCoolTimeText->SetText(FText::FromString(""));


				else if (ShadowCoolTimeText != mShadowCoolTimeText->GetText().ToString())
				{
					FString ZeroString = "0";

					if (ShadowCoolTimeText == ZeroString)
						ShadowCoolTimeText = FString::FromInt(++ShadowCoolTimeInt);

					mShadowCoolTimeText->SetText(FText::FromString(ShadowCoolTimeText));
				}

				if (CounterCoolTime == 0.f)
					mCounterCoolTimeText->SetText(FText::FromString(""));


				else if (CounterCoolTimeText != mCounterCoolTimeText->GetText().ToString())
				{
					FString ZeroString = "0";

					if (CounterCoolTimeText == ZeroString)
						CounterCoolTimeText = FString::FromInt(++CounterCoolTimeInt);

					mCounterCoolTimeText->SetText(FText::FromString(CounterCoolTimeText));
				}

				if (UltimateCoolTime == 0.f)
					mUltimateCoolTimeText->SetText(FText::FromString(""));


				else if (UltimateCoolTimeText != mUltimateCoolTimeText->GetText().ToString())
				{
					FString ZeroString = "0";

					if (UltimateCoolTimeText == ZeroString)
						UltimateCoolTimeText = FString::FromInt(++UltimateCoolTimeInt);

					mUltimateCoolTimeText->SetText(FText::FromString(UltimateCoolTimeText));
				}

				if (NightmareCoolTime == 0.f)
					mNightmareCoolTimeText->SetText(FText::FromString(""));


				else if (NightmareCoolTimeText != mNightmareCoolTimeText->GetText().ToString())
				{
					FString ZeroString = "0";

					if (NightmareCoolTimeText == ZeroString)
						NightmareCoolTimeText = FString::FromInt(++NightmareCoolTimeInt);

					mNightmareCoolTimeText->SetText(FText::FromString(NightmareCoolTimeText));
				}

			

				



			}

			

		}
		


	}



}
