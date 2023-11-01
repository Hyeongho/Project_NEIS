// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "ItemDropComponent.generated.h"

class AShooterItem;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SACPROJECT_API UItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemDropComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DropItem();

	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AShooterItem>> m_ItemArray;
};
