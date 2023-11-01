// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "AuroraTestController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AAuroraTestController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuroraTestController();

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* m_DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_DassAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_FreezeAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_UltimateAction;

private:
	class UAuroraAIAnimInstance* m_Anim;

protected:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

protected:
	virtual void SetupInputComponent() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Dass(const FInputActionValue& Value);
	void Freeze(const FInputActionValue& Value);
	void Ultimate(const FInputActionValue& Value);
};
