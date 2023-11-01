// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "TerraController.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ATerraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATerraController();

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* m_DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_MoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraRotation;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraAttack;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraGurad;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraSkillQ;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraSkillE;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* m_TerraSkillR;

private:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_IsInput;

private:
	class UTerraAnimInstance* m_Anim;

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
	void SetInput(bool Input)
	{
		m_IsInput = Input;
	}

	bool GetInput() const
	{
		return m_IsInput;
	}

public:
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void TerraRotation(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Gurad(const FInputActionValue& Value);
	void ReleaseGurad(const FInputActionValue& Value);
	void SkillQ(const FInputActionValue& Value);
	void SkillE(const FInputActionValue& Value);
	void SkillR(const FInputActionValue& Value);
};
