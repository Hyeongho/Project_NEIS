// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Component/CJH/ShooterInventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Item/CJH/ShooterWeapon.h"
#include "../../Item/CJH/ShooterAmmo.h"
#include "../../Item/CJH/ShooterHealPack.h"
#include "../DefaultPlayerState.h"
#include "ShooterPlayerController.h"
#include "../../UI/CJH/ShooterOverlayWidget.h"
#include "../../DefaultGameInstance.h"

AShooterCharacter::AShooterCharacter()
	: Super()
	// Camera variables
	, m_BaseTurnRate(1.0f)
	, m_BaseLookUpRate(1.0f)
	, m_HipTurnRate(1.0f)
	, m_HipLookUpRate(1.0f)
	, m_AimingTurnRate(0.3f)
	, m_AimingLookUpRate(0.3f)
	, m_CameraDefaultFOV(0.0f)	// set in BeginPlay
	, m_CameraZoomedFOV(35.0f)
	, m_CameraCurrentFOV(0.0f)
	, m_ZoomInterpSpeed(20.0f)

	// Crosshair variables
	, m_CrosshairSpreadMultiplier(0.0f)
	, m_CrosshairVelocityFactor(0.0f)
	, m_CrosshairInAirFactor(0.0f)
	, m_CrosshairAimingFactor(0.0f)
	, m_CrosshairShootingFactor(0.0f)

	// Combat variables
	, m_ShooterState(EShooterState::Unoccupied)
	, m_StunChance(0.25)

	// Input status variables
	, m_FireButtonPressed(false)
	, m_AimingButtonPressed(false)

	// Shooter status variables
	, m_Aiming(false)
	, m_Crouching(false)
	, m_BaseMovementSpeed(600.0f)
	, m_CrouchMovementSpeed(300.0f)

	// Other variables
	, m_StandingCapsuleHalfHeight(88.0f)
	, m_CrouchingCapsuleHalfHeight(54.0f)
	, m_MPTime(0.1f)
	, m_MPTimeACC(0.0f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// =================================== Scene Component =========================================
	
	// Set Capsule
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(32.0f, 88.0f);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::CapsuleBeginOverlap);
	CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &ThisClass::CapsuleEndOverlap);
	//CapsuleComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	SetRootComponent(CapsuleComp);

	// Set Mesh
	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	MeshComp->SetupAttachment(GetRootComponent());

	// Set SpringArm
	check(m_SpringArm);
	m_SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	m_SpringArm->TargetArmLength = 250.0f;
	m_SpringArm->bUsePawnControlRotation = true;
	m_SpringArm->bEnableCameraLag = true;
	m_SpringArm->CameraLagSpeed = 20.0f;
	m_SpringArm->SocketOffset = FVector(0.0f, 50.0f, 20.0f);
	m_SpringArm->SetupAttachment(GetRootComponent());

	// Set Camera
	check(m_Camera);
	m_Camera->bUsePawnControlRotation = false;
	m_Camera->SetupAttachment(m_SpringArm, USpringArmComponent::SocketName);

	// Set CameraInterp
	m_CameraInterpSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CameraInterpSceneComponent"));
	m_CameraInterpSceneComponent->SetRelativeLocation(FVector(150.0f, 0.0f, 10.0f));
	m_CameraInterpSceneComponent->SetupAttachment(m_Camera);

	// Create HandSceneComponent for Reloading
	m_HandSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HandSceneComponent"));


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	// =================================== Actor Component =========================================

	// Set CharacterMovement
	UCharacterMovementComponent* MoveComp = CastChecked<UCharacterMovementComponent>(GetMovementComponent());
	MoveComp->GravityScale = 1.0f;
	MoveComp->MaxAcceleration = 1024.0f;
	MoveComp->BrakingFrictionFactor = 2.0f;
	MoveComp->BrakingFriction = 0.0f;
	MoveComp->GroundFriction = 2.0f;
	MoveComp->BrakingDecelerationWalking = 2048.0f;

	MoveComp->bOrientRotationToMovement = false;
	MoveComp->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	MoveComp->JumpZVelocity = 600.0f;
	MoveComp->AirControl = 0.2f;

	// for test
	MoveComp->MaxWalkSpeed = 600.0f;

	// Set Inventory
	m_ShooterInventory = CreateDefaultSubobject<UShooterInventoryComponent>(TEXT("ShooterInventory"));
	m_ShooterInventory->SetOwnerCharacter(this);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_ShooterPC = Cast<AShooterPlayerController>(GetController());
	m_OverlayWidget = m_ShooterPC->GetShooterOverlayWidget();

	if (m_Camera)
	{
		m_CameraDefaultFOV = m_Camera->FieldOfView;
		m_CameraCurrentFOV = m_CameraDefaultFOV;
	}

	if (GetShooterInventory()->SpawnAtBeginPlay())
	{
		AShooterWeapon* DefaultWeapon = GetShooterInventory()->GetWeapon(0);
		EquipWeapon(DefaultWeapon);
	}

	UDefaultGameInstance* GameInst = Cast<UDefaultGameInstance>(GetGameInstance());
	if (IsValid(GameInst))
		GameInst->SetPlayerCharacter(this);
}

void AShooterCharacter::CapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AShooterCharacter::CapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AShooterCharacter::UpdateLookRates(float DeltaTime)
{
	if (m_Aiming)
	{
		m_BaseTurnRate = m_AimingTurnRate;
		m_BaseLookUpRate = m_AimingLookUpRate;
	}
	else
	{
		m_BaseTurnRate = m_HipTurnRate;
		m_BaseLookUpRate = m_HipLookUpRate;
	}
}

void AShooterCharacter::UpdateCameraFOV(float DeltaTime)
{
	if (m_Aiming)
		m_CameraCurrentFOV = FMath::FInterpTo(m_CameraCurrentFOV, m_CameraZoomedFOV, DeltaTime, m_ZoomInterpSpeed);
	else
		m_CameraCurrentFOV = FMath::FInterpTo(m_CameraCurrentFOV, m_CameraDefaultFOV, DeltaTime, m_ZoomInterpSpeed);

	if (m_Camera)
		m_Camera->SetFieldOfView(m_CameraCurrentFOV);
}

void AShooterCharacter::UpdateCrosshairSpread(float DeltaTime)
{
	FVector2D WalkSpeedRange = FVector2D(0.0f, 600.0f);
	FVector2D VelocityMultiplierRange = FVector2D(0.0f, 1.0f);
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.0f;

	m_CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());

	// Calculate crosshair in air factor
	if (GetCharacterMovement()->IsFalling())
		m_CrosshairInAirFactor = FMath::FInterpTo(m_CrosshairInAirFactor, 1.25f, DeltaTime, 2.25f);
	else
		m_CrosshairInAirFactor = FMath::FInterpTo(m_CrosshairInAirFactor, 0.0f, DeltaTime, 20.0f);

	// Calculate crosshair aiming factor
	if (m_Aiming)
		m_CrosshairAimingFactor = FMath::FInterpTo(m_CrosshairAimingFactor, 0.5f, DeltaTime, 20.0f);
	else
		m_CrosshairAimingFactor = FMath::FInterpTo(m_CrosshairAimingFactor, 0.0f, DeltaTime, 20.0f);

	// Calculate crosshair shooting factor
	if (GetShooterState() == EShooterState::Firing)
		m_CrosshairShootingFactor = FMath::FInterpTo(m_CrosshairShootingFactor, 0.1f, DeltaTime, 60.0f);
	else
		m_CrosshairShootingFactor = FMath::FInterpTo(m_CrosshairShootingFactor, 0.0f, DeltaTime, 60.0f);


	// Calculate crosshair spread mulitlier
	m_CrosshairSpreadMultiplier = 0.5f + m_CrosshairVelocityFactor + m_CrosshairInAirFactor - m_CrosshairAimingFactor + m_CrosshairShootingFactor;
}

void AShooterCharacter::UpdateCapsuleHalfHeight(float DeltaTime)
{
	float TargetCapsuleHalfHeight = 0.0f;

	if (m_Crouching)
		TargetCapsuleHalfHeight = m_CrouchingCapsuleHalfHeight;
	else
		TargetCapsuleHalfHeight = m_StandingCapsuleHalfHeight;

	const float InterpHalfHeight = FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), TargetCapsuleHalfHeight, DeltaTime, 5.0f);

	// Negative value if crouching / Positive value if standing
	const float DeltaCapsuleHalfHeight = InterpHalfHeight - GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const FVector MeshOffset = FVector(0.0f, 0.0f, -DeltaCapsuleHalfHeight);
	GetMesh()->AddLocalOffset(MeshOffset);

	GetCapsuleComponent()->SetCapsuleHalfHeight(InterpHalfHeight);
}

void AShooterCharacter::WeaponFire()
{
	if (GetShooterState() != EShooterState::Unoccupied)
		return;

	if (IsValid(m_EquippedWeapon))
		m_EquippedWeapon->WeaponFire();
}

void AShooterCharacter::EquipWeapon(AShooterWeapon* InWeapon)
{
	if (IsValid(InWeapon))
	{
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (HandSocket)
			HandSocket->AttachActor(InWeapon, GetMesh());

		m_EquippedWeapon = InWeapon;
		m_EquippedWeapon->SetShooterItemState(EShooterItemState::Equipped);
		m_EquippedWeapon->SetOwnerCharacter(this);

		m_OverlayWidget->SetCrosshairAmmo(m_EquippedWeapon->GetAmmo(), m_EquippedWeapon->GetMagazineCapacity());
		m_OverlayWidget->SetDisplayAmmoCurrent(m_EquippedWeapon->GetAmmo());
		m_OverlayWidget->SetDisplayAmmoMagazine(m_EquippedWeapon->GetMagazineAmmo());

		m_OverlayWidget->SetSlotEquipWeapon(m_EquippedWeapon->GetInventoryIndex());
	}
	else
	{
		m_EquippedWeapon = nullptr;
	}
}

void AShooterCharacter::DropWeapon()
{
	AShooterWeapon* AnotherWeapon = GetShooterInventory()->GetAnotherWeapon(m_EquippedWeapon);
	// 장착한 무기 말고 다른 무기가 없다면 취소
	if (!IsValid(AnotherWeapon))
		return;

	GetShooterInventory()->AddWeapon(nullptr, m_EquippedWeapon->GetInventoryIndex());
	m_EquippedWeapon->DropWeapon();

	EquipWeapon(AnotherWeapon);
}

void AShooterCharacter::StartAiming()
{
	m_Aiming = true;

	if(m_Crouching)
		GetCharacterMovement()->MaxWalkSpeed = m_CrouchMovementSpeed;
}

void AShooterCharacter::StopAiming()
{
	m_Aiming = false;

	if (!m_Crouching)
		GetCharacterMovement()->MaxWalkSpeed = m_BaseMovementSpeed;
}

void AShooterCharacter::WeaponChange(int32 InventoryIndex)
{
	if (InventoryIndex < 0 || InventoryIndex >= GetShooterInventory()->GetInventoryCapacity())
		return;

	if (GetShooterState() != EShooterState::Unoccupied)
		return;

	AShooterWeapon* SelectedWeapon = GetShooterInventory()->GetWeapon(InventoryIndex);
	if (IsValid(SelectedWeapon))
	{
		// 선택한 무기가 이미 장착하고 있는 무기면 아무것도 안함.
		if (m_EquippedWeapon == SelectedWeapon)
			return;

		// 무기 교체
		m_EquippedWeapon->SetShooterItemState(EShooterItemState::PickedUp);
		m_OverlayWidget->SetSlotUnEquipWeapon(m_EquippedWeapon->GetInventoryIndex());

		EquipWeapon(SelectedWeapon);

		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
		if (IsValid(AnimInst) && IsValid(m_EquipMontage))
		{
			AnimInst->Montage_Play(m_EquipMontage, 1.0f);
			AnimInst->Montage_JumpToSection(FName(TEXT("Equip")));

			SetShooterState(EShooterState::Equipping);
		}

	}
	else
	{
		// 선택한 슬롯에 무기가 없으면 아무것도 하지 않음.
		return;
	}
}

void AShooterCharacter::Stun()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInst) && IsValid(m_HitMontage))
	{
		m_ShooterState = EShooterState::Stunned;
		AnimInst->Montage_Play(m_HitMontage);
	}
}

void AShooterCharacter::Die()
{
	// 충돌 해제
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 입력 종료
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(PC))
	{
		DisableInput(PC);
	}

	// Death 애니메이션 재생
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInst) && IsValid(m_DeathMontage))
	{
		AnimInst->Montage_Play(m_DeathMontage);
		AnimInst->Montage_JumpToSection(FName("Death"));
	}
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCameraFOV(DeltaTime);

	UpdateLookRates(DeltaTime);

	UpdateCrosshairSpread(DeltaTime);

	UpdateCapsuleHalfHeight(DeltaTime);

	m_MPTimeACC += DeltaTime;

	if (m_MPTimeACC >= m_MPTime)
	{
		ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());
		if (IsValid(DefaultPlayerState))
		{
			DefaultPlayerState->AddMP(2);
		}

		m_MPTimeACC -= m_MPTime;
	}
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AShooterCharacter::TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation)
{
	FVector2D ViewportSize;

	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(ViewportSize);

	// 화면의 중앙
	FVector2D CrossHairLocation = FVector2D(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

	FVector CrossHairWorldPosition;
	FVector CrossHairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), CrossHairLocation, CrossHairWorldPosition, CrossHairWorldDirection);

	if (bScreenToWorld)
	{
		// Trace from crosshair world location outward
		const FVector Start = CrossHairWorldPosition;
		const FVector End = Start + CrossHairWorldDirection * 100'000.f;
		OutHitLocation = End;

		GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECollisionChannel::ECC_Visibility);

		if (OutHitResult.bBlockingHit)
		{
			OutHitLocation = OutHitResult.Location;

			return true;
		}
	}

	return false;
}

void AShooterCharacter::GetPickupItem(AShooterItem* InItem)
{
	AShooterWeapon* Weapon = Cast<AShooterWeapon>(InItem);
	if (IsValid(Weapon))
	{
		GetShooterInventory()->AddWeapon(Weapon);
	}

	AShooterAmmo* Ammo = Cast<AShooterAmmo>(InItem);
	if (IsValid(Ammo))
	{
		m_EquippedWeapon->AddAmmo(Ammo);
	}

	AShooterHealPack* HealPack = Cast<AShooterHealPack>(InItem);
	if (IsValid(HealPack))
	{
		ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());
		if (IsValid(DefaultPlayerState))
		{
			int32 HealAmount = HealPack->GetHealPercent() * DefaultPlayerState->GetHPMax();
			DefaultPlayerState->AddHP(HealAmount);
		}
	}


}

void AShooterCharacter::WeaponReload()
{
	if (GetShooterState() != EShooterState::Unoccupied)
		return;

	if (IsValid(m_EquippedWeapon))
	{
		if (m_EquippedWeapon->HasCarryingAmmo())
		{
			SetShooterState(EShooterState::Reloading);


			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (IsValid(AnimInstance) && IsValid(m_ReloadMontage))
			{
				FName ReloadMontageSectionName = m_EquippedWeapon->GetReloadMontageSectionName();

				AnimInstance->Montage_Play(m_ReloadMontage);
				AnimInstance->Montage_JumpToSection(ReloadMontageSectionName);
			}
		}
	}
}

void AShooterCharacter::GrapClip()
{
	if (!IsValid(m_EquippedWeapon))
		return;

	if (!IsValid(m_HandSceneComponent))
		return;

	FName ClipBoneName = m_EquippedWeapon->GetClipBoneName();
	int32 ClipBoneIndex = m_EquippedWeapon->GetWeaponMesh()->GetBoneIndex(ClipBoneName);
	m_ClipTransform = m_EquippedWeapon->GetWeaponMesh()->GetBoneTransform(ClipBoneIndex);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	m_HandSceneComponent->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("hand_l")));
	m_HandSceneComponent->SetWorldTransform(m_ClipTransform);

	m_EquippedWeapon->SetMovingClip(true);
}

void AShooterCharacter::ReplaceClip()
{
	m_EquippedWeapon->SetMovingClip(false);
}

void AShooterCharacter::ReloadFinish()
{
	SetShooterState(EShooterState::Unoccupied);

	if (!IsValid(m_EquippedWeapon))
		return;

	if (m_AimingButtonPressed)
		StartAiming();

	// Update Ammo
	m_EquippedWeapon->WeaponReload();
}

void AShooterCharacter::DeathFinish()
{
	GetMesh()->bPauseAnims = true;

	// 혹시나 죽으면 다시 시작
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("LoadingLevel_ToRuin"));
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());
	if (IsValid(DefaultPlayerState))
	{
		if (DefaultPlayerState->AddHP(-DamageAmount))
		{
			Die();
		}

		const float Stunned = FMath::FRandRange(0.0f, 1.0f);
		if (Stunned <= m_StunChance)
		{
			Stun();
		}
	}

	return DamageAmount;
}

void AShooterCharacter::SetShooterState(EShooterState InState)
{
	m_ShooterState = InState;
}

void AShooterCharacter::MoveAxis(const FInputActionValue& Value)
{
	if (GetShooterState() == EShooterState::Stunned)
		return;

	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	// Move Left/Right
	FVector RightDirection = UKismetMathLibrary::GetRightVector(FRotator(0.0, GetControlRotation().Yaw, GetControlRotation().Roll));
	AddMovementInput(RightDirection, LookAxisValue.X);

	// Move Forward/Backward
	FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(FRotator(0.0, GetControlRotation().Yaw, 0.0));
	AddMovementInput(ForwardDirection, LookAxisValue.Y);
}

void AShooterCharacter::MouseAxis(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisValue.X * m_BaseLookUpRate);
	AddControllerPitchInput(LookAxisValue.Y * m_BaseLookUpRate);
}

void AShooterCharacter::StartLeftClick(const FInputActionValue& Value)
{
	m_FireButtonPressed = true;

	WeaponFire();
}

void AShooterCharacter::StopLeftClick(const FInputActionValue& Value)
{
	m_FireButtonPressed = false;
}

void AShooterCharacter::StartRightClick(const FInputActionValue& Value)
{
	m_AimingButtonPressed = true;

	if (GetShooterState() != EShooterState::Reloading && GetShooterState() != EShooterState::Stunned)
		StartAiming();
}

void AShooterCharacter::StopRightClick(const FInputActionValue& Value)
{
	m_AimingButtonPressed = false;

	StopAiming();
}

void AShooterCharacter::StartSpaceBar(const FInputActionValue& Value)
{
	Super::Jump();

	if (m_Crouching)
	{
		m_Crouching = false;
		GetCharacterMovement()->MaxWalkSpeed = m_BaseMovementSpeed;
	}
}

void AShooterCharacter::StopSpaceBar(const FInputActionValue& Value)
{
	Super::StopJumping();
}

void AShooterCharacter::StartCtrlKey(const FInputActionValue& Value)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		m_Crouching = true;
	}
	if (m_Crouching)
		GetCharacterMovement()->MaxWalkSpeed = m_CrouchMovementSpeed;
}

void AShooterCharacter::StopCtrlKey(const FInputActionValue& Value)
{
	m_Crouching = false;
	if (!m_Crouching)
		GetCharacterMovement()->MaxWalkSpeed = m_BaseMovementSpeed;
}

void AShooterCharacter::StartShiftKey(const FInputActionValue& Value)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());
		if (IsValid(DefaultPlayerState))
		{
			if (DefaultPlayerState->GetMP() >= 50)
			{
				FVector Velocity = GetVelocity();
				Velocity.Z = 0.0f;
				Velocity.Normalize();

				LaunchCharacter(Velocity * 3000.f, false, false);

				DefaultPlayerState->AddMP(-50);

				if (IsValid(m_DashSound))
					UGameplayStatics::PlaySound2D(this, m_DashSound);
			}
		}
	}
}

void AShooterCharacter::StopShiftKey(const FInputActionValue& Value)
{
}

void AShooterCharacter::StartRKey(const FInputActionValue& Value)
{
	WeaponReload();
}

void AShooterCharacter::StopRKey(const FInputActionValue& Value)
{
}

void AShooterCharacter::StartQKey(const FInputActionValue& Value)
{
}

void AShooterCharacter::StopQKey(const FInputActionValue& Value)
{
}

void AShooterCharacter::StartEKey(const FInputActionValue& Value)
{
	DropWeapon();
}

void AShooterCharacter::StopEKey(const FInputActionValue& Value)
{
}

void AShooterCharacter::Start1Key(const FInputActionValue& Value)
{
	WeaponChange(0);
}

void AShooterCharacter::Stop1Key(const FInputActionValue& Value)
{
}

void AShooterCharacter::Start2Key(const FInputActionValue& Value)
{
	WeaponChange(1);
}

void AShooterCharacter::Stop2Key(const FInputActionValue& Value)
{
}

void AShooterCharacter::Start3Key(const FInputActionValue& Value)
{
	WeaponChange(2);
}

void AShooterCharacter::Stop3Key(const FInputActionValue& Value)
{
}

void AShooterCharacter::Start4Key(const FInputActionValue& Value)
{
	WeaponChange(3);
}

void AShooterCharacter::Stop4Key(const FInputActionValue& Value)
{
}
