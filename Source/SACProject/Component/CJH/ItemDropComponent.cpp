// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropComponent.h"
#include "../../Item/CJH/ShooterItem.h"

// Sets default values for this component's properties
UItemDropComponent::UItemDropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemDropComponent::DropItem()
{
	int32 ItemCount = m_ItemArray.Num();
	if (ItemCount == 0)
		return;

	// 80퍼센트로 아이템 드랍
	const float Chance = FMath::FRandRange(0.0f, 1.0f);
	if (Chance <= 0.8f)
	{
		const int32 RandomNumber = FMath::RandRange(1, ItemCount);

		FVector SpawnLocation = GetOwner()->GetActorLocation();
		//SpawnLocation.Z += 100.0f;

		AShooterItem* DropedItem = GetWorld()->SpawnActor<AShooterItem>(m_ItemArray[RandomNumber - 1], SpawnLocation, GetOwner()->GetActorRotation());
		DropedItem->DropItem();
	}
}


// Called every frame
//void UItemDropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

