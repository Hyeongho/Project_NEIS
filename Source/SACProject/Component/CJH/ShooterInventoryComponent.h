// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "ShooterInventoryComponent.generated.h"

class AShooterWeapon;


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SACPROJECT_API UShooterInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShooterInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AShooterWeapon* SpawnDefaultWeapon();

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SpawnAtBeginPlay();

	bool IsFull() const;

	/* nullptr 추가 불가능, 슬롯이 빈 순서대로 채워짐 */
	bool AddWeapon(AShooterWeapon* InWeapon);

	/* nullptr 추가 가능, 인덱스가 유효하지 않으면 안됨, nullptr을 넣으면 슬롯이 비게됨 */
	bool AddWeapon(AShooterWeapon* InWeapon, int32 InventoryIndex);

	/* 유효한 Index일 경우 해당 슬롯의 weapon을 반환, 해당 슬롯에 weapon이 없을 경우 nullptr을 반환 */
	AShooterWeapon* GetWeapon(int32 InventoryIndex);

	/* InWeapon으로 들어간 Weapon과 다른 Weapon을 반환한다. InWewapon이 nullptr일 경우와 InWeapon과 다른 Weapon이 없을 경우 nullptr을 반환 */
	AShooterWeapon* GetAnotherWeapon(AShooterWeapon* InWeapon);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<AShooterWeapon>> m_Inventory;

	// 무기 슬롯 최대치
	const int32 INVENTORY_CAPACITY = 4;

	// 1번 슬롯 기본무기
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TSubclassOf<AShooterWeapon> m_DefaultWeaponClass;

	TObjectPtr<AShooterCharacter> m_OwnerCharacter;

/* Getter */
public:
	FORCEINLINE const int32 GetInventoryCapacity() const { return INVENTORY_CAPACITY; }

/* Setter */
public:
	void SetOwnerCharacter(AShooterCharacter* InCharacter);
};
