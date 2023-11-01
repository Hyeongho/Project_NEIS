// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AShooterCharacter;
class UShooterOverlayWidget;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Default Constructor */
	AShooterPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> m_ShooterIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MoveIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MouseIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_LeftClickIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_RightClickIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_SpaceBarIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_CtrlKeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_ShiftKeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_RkeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_QkeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_EkeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_1keyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_2keyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_3keyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_4keyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FVector2D m_ViewPitchLimit = FVector2D(-65.0f, 65.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UShooterOverlayWidget> m_OverlayWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Widget", meta = (AllowPrivateAccess = true))
	TObjectPtr<UShooterOverlayWidget> m_OverlayWidget;

public:
	FORCEINLINE UShooterOverlayWidget* GetShooterOverlayWidget() const { return m_OverlayWidget; }

protected:
	void MoveAxis(const FInputActionValue& Value);
	void MouseAxis(const FInputActionValue& Value);
	void StartLeftClick(const FInputActionValue& Value);
	void StopLeftClick(const FInputActionValue& Value);
	void StartRightClick(const FInputActionValue& Value);
	void StopRightClick(const FInputActionValue& Value);
	void StartSpaceBar(const FInputActionValue& Value);
	void StopSpaceBar(const FInputActionValue& Value);
	void StartCtrlKey(const FInputActionValue& Value);
	void StopCtrlKey(const FInputActionValue& Value);
	void StartShiftKey(const FInputActionValue& Value);
	void StopShiftKey(const FInputActionValue& Value);
	void StartRKey(const FInputActionValue& Value);
	void StopRKey(const FInputActionValue& Value);
	void StartQKey(const FInputActionValue& Value);
	void StopQKey(const FInputActionValue& Value);
	void StartEKey(const FInputActionValue& Value);
	void StopEKey(const FInputActionValue& Value);
	void Start1Key(const FInputActionValue& Value);
	void Stop1Key(const FInputActionValue& Value);
	void Start2Key(const FInputActionValue& Value);
	void Stop2Key(const FInputActionValue& Value);
	void Start3Key(const FInputActionValue& Value);
	void Stop3Key(const FInputActionValue& Value);
	void Start4Key(const FInputActionValue& Value);
	void Stop4Key(const FInputActionValue& Value);

	AShooterCharacter* GetShooterCharacter() const;
};
