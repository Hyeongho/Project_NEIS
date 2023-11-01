// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "Kwang_Controller.generated.h"

class AKwang_PlayerCharacter;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AKwang_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	AKwang_Controller();

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* m_DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_AttackAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_DashAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_MoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_Rotation; // Mouse Position

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_Skill1Action; // Mouse RightClick

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_Skill2Action; // Keyboard Q Input

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_Skill3Action; // Keyboard E Input

private:
	bool m_MovePossible;

public:
	void MovePossible(bool Possible = true) { m_MovePossible = Possible; }

protected:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetupInputComponent() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void AttackAction(const FInputActionValue& Value);
	void DashAction(const FInputActionValue& Value);
	void MoveAction(const FInputActionValue& Value);
	void RotationCharacter(const FInputActionValue& Value);
	void Skill1Action(const FInputActionValue& Value);
	void Skill1ReleaseAction(const FInputActionValue& Value);
	void Skill2Action(const FInputActionValue& Value);
	void Skill3Action(const FInputActionValue& Value);

public:
	void Skill1Release();

private:
	AKwang_PlayerCharacter* GetPlayerCharacter() const;
};
