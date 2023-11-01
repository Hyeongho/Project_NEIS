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
	Pickup			UMETA(DisplayName = "Pickup"),			// 바닥에 있어서 pickup 가능할 때
	PickingUp		UMETA(DisplayName = "PickingUp"),		// pickup 중
	PickedUp		UMETA(DisplayName = "PickedUp"),		// pickup 완료
	Equipped		UMETA(DisplayName = "Equipped"),		// 장착 (무기)
	Failling		UMETA(DisplayName = "Failling"),		// drop 중

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

	/* 아이템 상태에 따라 property 조정 */
	virtual void SetItemProperties(EShooterItemState InState);

	/* 아이템과 충돌시 획득용 */
	void PickedUp(AShooterCharacter* InCharacter);

	/* 아이템 획득시 이동효과 시작 */
	void StartItemZCurve();

	/* 아이템 획득시 이동효과 타이머 종료 */
	void FinishItemZCurve();

	/* 캐릭터가 아이템을 습득하고 난 후 실행 */
	virtual void OnFinishItemZCurve();

	/* 아이템이 PickingUp 상태일 때 동작 */
	void ItemInterp(float DeltaTime);

	void PlayPickupSound();
	void PlayPickedUpSound();

	void FinishItemDrop();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DropItem();

protected:
	///* 아이템 탐지범위 충돌용 */
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	//TObjectPtr<USphereComponent> m_AreaSphere;

	/* 아이템 소유 캐릭터 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterCharacter> m_OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	EShooterItemState m_ShooterItemState;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	EShooterItemType m_ShooterItemType;

/* pickup시 효과 */
protected:
	/* 아이템 pickup 시 이동 연출을 위한 curve asset */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> m_ItemZCurve;

	/* 아이템 pickup 시 크기 연출을 위한 curve asset */
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
