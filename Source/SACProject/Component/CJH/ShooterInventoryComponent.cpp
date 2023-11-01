// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterInventoryComponent.h"
#include "../../Item/CJH/ShooterWeapon.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "../../UI/CJH/ShooterOverlayWidget.h"

// Sets default values for this component's properties
UShooterInventoryComponent::UShooterInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// 기본 슬롯 확보
	for (int32 i = 0; i < INVENTORY_CAPACITY; ++i)
	{
		m_Inventory.Add(nullptr);
	}
}


// Called when the game starts
void UShooterInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

AShooterWeapon* UShooterInventoryComponent::SpawnDefaultWeapon()
{
	if (IsValid(m_DefaultWeaponClass))
		return GetWorld()->SpawnActor<AShooterWeapon>(m_DefaultWeaponClass);

	return nullptr;
}

bool UShooterInventoryComponent::SpawnAtBeginPlay()
{
	// 기본 무기 생성
	AShooterWeapon* DefaultWeapon = SpawnDefaultWeapon();
	if (IsValid(DefaultWeapon))
	{
		AddWeapon(DefaultWeapon, 0);
		return true;
	}
	else
		return false;
}

bool UShooterInventoryComponent::IsFull() const
{
	for (int32 i = 0; i < INVENTORY_CAPACITY; ++i)
	{
		if (!IsValid(m_Inventory[i]))
			return false;
	}
	return true;
}

bool UShooterInventoryComponent::AddWeapon(AShooterWeapon* InWeapon)
{
	if (!IsValid(InWeapon))
		return false;

	if (IsFull())
		return false;

	for (int32 i = 0; i < INVENTORY_CAPACITY; ++i)
	{
		if (!IsValid(m_Inventory[i]))
		{
			m_Inventory[i] = InWeapon;
			InWeapon->SetInventoryIndex(i);
			m_OwnerCharacter->GetShooterOverlayWidget()->SetSlotWeapon(InWeapon, i);

			return true;
		}
	}

	return false;
}

bool UShooterInventoryComponent::AddWeapon(AShooterWeapon* InWeapon, int32 InventoryIndex)
{
	if (InventoryIndex < 0 || InventoryIndex >= INVENTORY_CAPACITY)
		return false;

	if (IsFull())
		return false;

	m_Inventory[InventoryIndex] = InWeapon;

	if (IsValid(InWeapon))
	{
		InWeapon->SetInventoryIndex(InventoryIndex);
		m_OwnerCharacter->GetShooterOverlayWidget()->SetSlotWeapon(InWeapon, InventoryIndex);
	}

	return true;
}

AShooterWeapon* UShooterInventoryComponent::GetWeapon(int32 InventoryIndex)
{
	if (InventoryIndex < 0 || InventoryIndex >= INVENTORY_CAPACITY)
		return nullptr;

	return m_Inventory[InventoryIndex];
}

AShooterWeapon* UShooterInventoryComponent::GetAnotherWeapon(AShooterWeapon* InWeapon)
{
	if (!IsValid(InWeapon))
		return nullptr;

	for (int32 i = 0; i < INVENTORY_CAPACITY; ++i)
	{
		if (IsValid(m_Inventory[i]))
		{
			if (m_Inventory[i] != InWeapon)
				return m_Inventory[i];
		}
	}

	return nullptr;
}

void UShooterInventoryComponent::SetOwnerCharacter(AShooterCharacter* InCharacter)
{
	m_OwnerCharacter = InCharacter;
}


// Called every frame
//void UShooterInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

