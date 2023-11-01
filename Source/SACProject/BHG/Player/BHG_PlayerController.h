// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "BHG_PlayerController.generated.h"

UCLASS()
class SACPROJECT_API ABHG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABHG_PlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> m_YinIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MoveIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MouseIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MouseLeftClickIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_MouseRightClickIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_SpaceKeyIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_QButtonIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_EButtonIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_Num1ButtonIA;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_Num2ButtonIA;

protected:
	virtual void SetupInputComponent() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;


private:	//Bind Action
	void MoveAction(const FInputActionValue& Value);
	void RotationCharacterAction(const FInputActionValue& Value);
	void MouseLeftClickAction(const FInputActionValue& Value);
	void MouseRightClickAction(const FInputActionValue& Value);
	void QKeyAction(const FInputActionValue& Value);
	void EKeyAction(const FInputActionValue& Value);
	void Num1KeyAction(const FInputActionValue& Value);
	void Num2KeyAction(const FInputActionValue& Value);
	void SpaceKeyAction(const FInputActionValue& Value);
	
};
