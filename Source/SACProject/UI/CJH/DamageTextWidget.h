// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDamageTextWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateLocation();

public:
	void SetDamageText(int32 Damage, const FVector& HitLocation);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> m_DamageText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DamageTextAnim;

	FVector m_DamageLocation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	float m_DestroyTime;

	float m_DestroyTimeAcc;
};
