// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UImage;
class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCrosshairWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_CrosshairTop;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_CrosshairBottom;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_CrosshairLeft;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_CrosshairRight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UImage> m_CrosshairDot;

	FVector2D m_TopPosition;
	FVector2D m_BottomPosition;
	FVector2D m_LeftPosition;
	FVector2D m_RightPosition;

	TObjectPtr<AShooterCharacter> m_OwnerCharacter;
	float m_CrosshairMuliplier;
	float m_CrosshairSpreadMax;

public:
	void SetOwnerCharacter(AShooterCharacter* InCharacter);
};
