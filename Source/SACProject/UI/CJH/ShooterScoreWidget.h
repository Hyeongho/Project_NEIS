// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ShooterScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UShooterScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UShooterScoreWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetCurrentScoreText(int32 Score);
	void PlayCurrentScoreAnim();
	void SetMaxScoreText(int32 Score);

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_CurrentScoreText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> CurrentScoreTextAnim;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_MaxScoreText;
};
