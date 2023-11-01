// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AICharacter.h"
#include "IS_AICharacter.generated.h"

class UWidgetComponent;
class UDamageTextWidget;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AIS_AICharacter : public AAICharacter
{
	GENERATED_BODY()
	
public:
	AIS_AICharacter();

protected: 
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCoolDownComponent> m_AttackCooldownComp;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool	m_IsElite;

protected: // Widget
	UPROPERTY(Category = "UIWidget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent>		m_Widget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UIWidget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;

protected:	// Dissolve
	TArray<TObjectPtr<UMaterialInstanceDynamic>>	m_MtrlArray;
	bool	m_DissEnable;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_DissTime;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float	m_DissCurTime;


protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void ShootFireBomb(FVector TargetLoc);
	void DeathEnd();
	
};
