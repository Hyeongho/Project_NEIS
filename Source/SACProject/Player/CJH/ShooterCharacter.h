// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../PlayerCharacter.h"
#include "ShooterCharacter.generated.h"

class UShooterInfoComponent;
class UShooterInventoryComponent;
class AShooterItem;
class AShooterWeapon;
class AShooterPlayerController;
class UShooterOverlayWidget;
class USoundCue;

UENUM(BlueprintType)
enum class EShooterState : uint8
{
	Unoccupied	UMETA(DisplayName = "Unoccupied"),
	Firing		UMETA(DisplayName = "Firing"),
	Reloading	UMETA(DisplayName = "Reloading"),
	Equipping	UMETA(DisplayName = "Equipping"),
	Stunned		UMETA(DisplayName = "Stunned"),

	MAX			UMETA(DisplayName = "DefaultMAX")
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Update look rates based on aiming */
	void UpdateLookRates(float DeltaTime);

	/* Update Camera FOV when aiming */
	void UpdateCameraFOV(float DeltaTime);

	/* Update crosshair spread muliplier */
	void UpdateCrosshairSpread(float DeltaTime);

	/* Update half height of CapsuleComponent based on crouching / standing */
	void UpdateCapsuleHalfHeight(float DeltaTime);

	void WeaponFire();

	void EquipWeapon(AShooterWeapon* InWeapon);

	void DropWeapon();

	void StartAiming();

	void StopAiming();

	void WeaponChange(int32 InventoryIndex);

	void Stun();

	void Die();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);

	void GetPickupItem(AShooterItem* InItem);

	void WeaponReload();

	void GrapClip();
	void ReplaceClip();
	void ReloadFinish();
	void DeathFinish();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/*
	* Component
	*/
private:
	/* SceneComponent to get distance for the interp destination */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> m_CameraInterpSceneComponent;

	/* SceneComponent to attach to the Character's hand during reloading */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> m_HandSceneComponent;

	/* ShooterCharacter's Inventory */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UShooterInventoryComponent> m_ShooterInventory;

	/*
	* Camera variables
	*/
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	float m_BaseTurnRate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	float m_BaseLookUpRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float m_HipTurnRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float m_HipLookUpRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float m_AimingTurnRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float m_AimingLookUpRate;

	/* Default Camera field of view */
	float m_CameraDefaultFOV;

	/* Field of view when zoomed in */
	float m_CameraZoomedFOV;

	/* Current field of view */
	float m_CameraCurrentFOV;

	/* Interpolation speed for zooming when aiming */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	float m_ZoomInterpSpeed;

	/*
	* Crosshair variables -> 아마도 무기별로 달라야 할 듯?
	*/
private:
	/* Determines the spread of the crosshairs */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrossHair", meta = (AllowPrivateAccess = true))
	float m_CrosshairSpreadMultiplier;

	/* Velocity for crosshair spread */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrossHair", meta = (AllowPrivateAccess = true))
	float m_CrosshairVelocityFactor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrossHair", meta = (AllowPrivateAccess = true))
	float m_CrosshairInAirFactor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrossHair", meta = (AllowPrivateAccess = true))
	float m_CrosshairAimingFactor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrossHair", meta = (AllowPrivateAccess = true))
	float m_CrosshairShootingFactor;

	/**
	* Combat
	*/
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<AShooterWeapon> m_EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	EShooterState m_ShooterState;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage>	m_FireMontage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage>	m_ReloadMontage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_EquipMontage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	FTransform m_ClipTransform;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_HitMontage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float m_StunChance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> m_DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundCue> m_DashSound;


	/*
	* Input status variables
	*/
private:
	bool m_FireButtonPressed;
	bool m_AimingButtonPressed;

	/*
	* Shooter Status variables
	*/
private:
	bool m_Aiming;
	bool m_Crouching;

	/* Regular movement speed */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_BaseMovementSpeed;

	/* Crouch movement speed */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_CrouchMovementSpeed;

	/*
	* Other variables
	*/
private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_StandingCapsuleHalfHeight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_CrouchingCapsuleHalfHeight;

	TObjectPtr<AShooterPlayerController> m_ShooterPC;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Widget", meta = (AllowPrivateAccess = true))
	TObjectPtr<UShooterOverlayWidget> m_OverlayWidget;

	float m_MPTime;
	float m_MPTimeACC;

	/*
	* Getter
	*/
public:
	FORCEINLINE UCameraComponent* GetCamera() const { return m_Camera; }
	FORCEINLINE FVector GetCameraInterpLocation() const { return m_CameraInterpSceneComponent->GetComponentLocation(); }
	FORCEINLINE USceneComponent* GetHandSceneComponent() const { return m_HandSceneComponent; }
	FORCEINLINE UShooterInventoryComponent* GetShooterInventory() const { return m_ShooterInventory; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const { return m_CrosshairSpreadMultiplier; }

	FORCEINLINE EShooterState GetShooterState() const { return m_ShooterState; }
	FORCEINLINE bool GetFireButtonPressed() const { return m_FireButtonPressed; }
	FORCEINLINE bool GetAimingButtonPressed() const { return m_AimingButtonPressed; }
	FORCEINLINE bool IsAiming() const { return m_Aiming; }
	FORCEINLINE bool IsCrouching() const { return m_Crouching; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UShooterOverlayWidget* GetShooterOverlayWidget() const { return m_OverlayWidget; }

	/*
	* Setter
	*/
public:
	void SetShooterState(EShooterState InState);






	/*
	* Input Functions
	*/
public:
	void MoveAxis(const FInputActionValue& Value);
	void MouseAxis(const FInputActionValue& Value);
	void StartLeftClick(const FInputActionValue& Value);
	void StopLeftClick(const FInputActionValue& Value);
	void StartRightClick(const FInputActionValue& Value);
	void StopRightClick(const FInputActionValue& Value);
	void StartSpaceBar(const FInputActionValue& Value);
	void StopSpaceBar(const FInputActionValue& Value);
	void StartCtrlKey(const FInputActionValue& Value);
	void StopCtrlKey(const FInputActionValue& Value);
	void StartShiftKey(const FInputActionValue& Value);
	void StopShiftKey(const FInputActionValue& Value);
	void StartRKey(const FInputActionValue& Value);
	void StopRKey(const FInputActionValue& Value);
	void StartQKey(const FInputActionValue& Value);
	void StopQKey(const FInputActionValue& Value);
	void StartEKey(const FInputActionValue& Value);
	void StopEKey(const FInputActionValue& Value);
	void Start1Key(const FInputActionValue& Value);
	void Stop1Key(const FInputActionValue& Value);
	void Start2Key(const FInputActionValue& Value);
	void Stop2Key(const FInputActionValue& Value);
	void Start3Key(const FInputActionValue& Value);
	void Stop3Key(const FInputActionValue& Value);
	void Start4Key(const FInputActionValue& Value);
	void Stop4Key(const FInputActionValue& Value);
};
