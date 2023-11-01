// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ShooterItem.h"
#include "ShooterWeapon.generated.h"

class UNiagaraSystem;
class AShooterAmmo;

UENUM(BlueprintType)
enum class EShooterWeaponType : uint8
{
	SubmachineGun	UMETA(DisplayName = "SubmachineGun"),
	AssaultRifle	UMETA(DisplayName = "AssaultRifle"),
	Shotgun			UMETA(DisplayName = "Shotgun"),
	GrenadeLauncher	UMETA(DisplayName = "GrenadeLauncher"),

	MAX				UMETA(DisplayName = "DefaultMAX")
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterWeapon : public AShooterItem
{
	GENERATED_BODY()

public:
	AShooterWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetItemProperties(EShooterItemState InState) override;

	/* Called when WeaponFire */
	void DecrementAmmo();

	/* ���� Ammo�� Magazine�� Ammo�� MagazineCapacity ��ŭ Update */
	void UpdateMagazineAmmo();

	void ReloadAmmo(int32 AmmoAmount);

	void WeaponFalling();

	void FinishFalling();

	virtual void SendBullet();
	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult);

	void StartFireTimer();
	void AutoFireReset();

	void PlayFireSound();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void WeaponFire();

	bool HasAmmo();

	bool HasCarryingAmmo();

	bool IsClipFull();

	bool PickupAmmo();

	bool IsFiring();

	void WeaponReload();

	void AddAmmo(AShooterAmmo* InAmmo);

	void DropWeapon();

	//virtual void DropItem() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> m_WeaponMesh;

	/* �Ѿ� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	int32 m_Ammo;

	/* źâ�� �ִ� �Ѿ� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	int32 m_MagazineAmmo;

	/* �� ���� ������ ������ źâ �뷮 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	int32 m_MagazineCapacity;

	/* ���� ���� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	EShooterWeaponType m_ShooterWeaponType;

	/* ������ �� źâ�� �����̰� �ִ��� */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	bool m_MovingClip;

	/* ���� ���̷��濡�� źâ�� Bone �̸� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	FName m_ClipBoneName;

	/* ������ �� ����� �ִϸ��̼��� Section �̸� */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	FName m_ReloadMontageSectionName;

/* Fire */
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue>	m_FireSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_MuzzleFlashParticle;

	/* Spawned upon bullet impact */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_ImpactMapParticle;

	/* Spawned upon bullet impact */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UParticleSystem>	m_ImpactParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem>	m_BeamParticleSystem;



	/* true when we can fire. false when waiting for the timer */
	bool bShouldFire;

	FTimerHandle m_AutoFireTimer;

	/* ���� ���� �ӵ� */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	float m_AutoFireRate;

	/* ��������� */
	bool m_FiringBullet;

	/* �� �����Ÿ� */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	float m_WeaponFireRange;

	/* �� ������ */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Property", meta = (AllowPrivateAccess = true))
	int32 m_WeaponDamage;

	int32 m_InventoryIndex;



// Getter
public:
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return m_WeaponMesh; }
	FORCEINLINE int32 GetAmmo() const { return m_Ammo; }
	FORCEINLINE int32 GetMagazineAmmo() const { return m_MagazineAmmo; }
	FORCEINLINE int32 GetMagazineCapacity() const { return m_MagazineCapacity; }
	FORCEINLINE EShooterWeaponType GetShooterWeaponType() const { return m_ShooterWeaponType; }
	FORCEINLINE bool GetMovingClip() const { return m_MovingClip; }
	FORCEINLINE const FName& GetClipBoneName() const { return m_ClipBoneName; }
	FORCEINLINE const FName& GetReloadMontageSectionName() const { return m_ReloadMontageSectionName; }
	FORCEINLINE int32 GetWeaponDamage() const { return m_WeaponDamage; }
	FORCEINLINE int32 GetInventoryIndex() const { return m_InventoryIndex; }

// Setter
public:
	int32 SetAmmo(int32 InAmmo);
	int32 SetMagazineAmmo(int32 InAmmo);
	bool SetMovingClip(bool Move);
	int32 SetInventoryIndex(int32 InIndex);

};
