// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../../Player/PlayerCharacter.h"
#include "BHG_UltimateShadow.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_UltimateShadow : public APlayerCharacter
{
	GENERATED_BODY()

public:
	ABHG_UltimateShadow();

protected:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseEffect>	m_ShadowEffect;


	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;
	TObjectPtr<AActor> mOwnerActor;

public:
	void SetOwnerActor(class AActor* OwnerActor);
	void SetDestorySpawner();
	void SetDestoryEffect();

public:
	AActor* GetShadowOwnerActor() const { return mOwnerActor; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
