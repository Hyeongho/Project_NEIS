// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../DefaultItem.h"
#include "ShooterItem.generated.h"

class AShooterCharacter;
class UCurveFloat;
class UCurveVector;
class USoundCue;

UENUM(BlueprintType)
enum class EShooterItemState : uint8
{
	Pickup			UMETA(DisplayName = "Pickup"),			// �ٴڿ� �־ pickup ������ ��
	PickingUp		UMETA(DisplayName = "PickingUp"),		// pickup ��
	PickedUp		UMETA(DisplayName = "PickedUp"),		// pickup �Ϸ�
	Equipped		UMETA(DisplayName = "Equipped"),		// ���� (����)
	Failling		UMETA(DisplayName = "Failling"),		// drop ��

	MAX				UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EShooterItemType : uint8
{
	Weapon		UMETA(DisplayName = "Weapon"),
	Ammo		UMETA(DisplayName = "Ammo"),
	HealPack	UMETA(DisplayName = "HealPack"),

	MAX			UMETA(DisplayName = "MAX")
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterItem : public ADefaultItem
{
	GENERATED_BODY()

public:
	AShooterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnCollisionBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void OnAreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnAreaSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* ������ ���¿� ���� property ���� */
	virtual void SetItemProperties(EShooterItemState InState);

	/* �����۰� �浹�� ȹ��� */
	void PickedUp(AShooterCharacter* InCharacter);

	/* ������ ȹ��� �̵�ȿ�� ���� */
	void StartItemZCurve();

	/* ������ ȹ��� �̵�ȿ�� Ÿ�̸� ���� */
	void FinishItemZCurve();

	/* ĳ���Ͱ� �������� �����ϰ� �� �� ���� */
	virtual void OnFinishItemZCurve();

	/* �������� PickingUp ������ �� ���� */
	void ItemInterp(float DeltaTime);

	void PlayPickupSound();
	void PlayPickedUpSound();

	void FinishItemDrop();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DropItem();

protected:
	///* ������ Ž������ �浹�� */
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	//TObjectPtr<USphereComponent> m_AreaSphere;

	/* ������ ���� ĳ���� */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterCharacter> m_OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	EShooterItemState m_ShooterItemState;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	EShooterItemType m_ShooterItemType;

/* pickup�� ȿ�� */
protected:
	/* ������ pickup �� �̵� ������ ���� curve asset */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> m_ItemZCurve;

	/* ������ pickup �� ũ�� ������ ���� curve asset */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> m_ItemScaleCurve;

	FTimerHandle m_ItemInterpTimer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	float m_ZCurveTime;

	float m_ItemInterpX;
	float m_ItemInterpY;
	float m_InterpInitialYawOffset;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	FVector m_ItemInterpStartLocation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_PickupSound;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_PickedUpSound;

	FTimerHandle m_ItemDropTimer;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	float m_ItemDropTime;


/* Getter */
public:
	//FORCEINLINE USphereComponent* GetAreaSphere() const { return m_AreaSphere; }

	UFUNCTION(BlueprintCallable)
	AShooterCharacter* GetOwnerCharacter() const { return m_OwnerCharacter; }

	FORCEINLINE EShooterItemState GetShooterItemState() const { return m_ShooterItemState; }
	FORCEINLINE EShooterItemType GetShooterItemType() const { return m_ShooterItemType; }
	FORCEINLINE USoundCue* GetPickupSound() const { return m_PickupSound; }
	FORCEINLINE USoundCue* GetPickedUpSound() const { return m_PickedUpSound; }

/* Setter */
public:
	void SetOwnerCharacter(AShooterCharacter* InCharacter);
	void SetShooterItemState(EShooterItemState InState);
	void SetShooterItemType(EShooterItemType InType);
	
};
