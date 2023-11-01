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

	/* nullptr �߰� �Ұ���, ������ �� ������� ä���� */
	bool AddWeapon(AShooterWeapon* InWeapon);

	/* nullptr �߰� ����, �ε����� ��ȿ���� ������ �ȵ�, nullptr�� ������ ������ ��Ե� */
	bool AddWeapon(AShooterWeapon* InWeapon, int32 InventoryIndex);

	/* ��ȿ�� Index�� ��� �ش� ������ weapon�� ��ȯ, �ش� ���Կ� weapon�� ���� ��� nullptr�� ��ȯ */
	AShooterWeapon* GetWeapon(int32 InventoryIndex);

	/* InWeapon���� �� Weapon�� �ٸ� Weapon�� ��ȯ�Ѵ�. InWewapon�� nullptr�� ���� InWeapon�� �ٸ� Weapon�� ���� ��� nullptr�� ��ȯ */
	AShooterWeapon* GetAnotherWeapon(AShooterWeapon* InWeapon);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<AShooterWeapon>> m_Inventory;

	// ���� ���� �ִ�ġ
	const int32 INVENTORY_CAPACITY = 4;

	// 1�� ���� �⺻����
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
