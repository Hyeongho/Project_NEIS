// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "../../AI/CJH/BulletHit.h"
#include "../../AI/CJH/ShooterMonster.h"
#include "ShooterAmmo.h"
#include "../../UI/CJH/ShooterOverlayWidget.h"

AShooterWeapon::AShooterWeapon()
	: Super()
	, m_Ammo(30)
	, m_MagazineAmmo(120)
	, m_MagazineCapacity(30)
	, m_ShooterWeaponType(EShooterWeaponType::SubmachineGun)
	, m_MovingClip(false)
	, m_ClipBoneName(TEXT("smg_clip"))	// Belica gun의 clipname
	, m_AutoFireRate(0.1f)
	, m_FiringBullet(false)
	, m_WeaponFireRange(50'000.f)
	, m_WeaponDamage(20)
	, m_InventoryIndex(INDEX_NONE)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	m_WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_WeaponMesh->SetupAttachment(GetRootComponent());

	GetItemMesh()->SetVisibility(false);

	SetShooterItemType(EShooterItemType::Weapon);
}

void AShooterWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AShooterWeapon::SetItemProperties(EShooterItemState InState)
{
	Super::SetItemProperties(InState);

	switch (InState)
	{
	case EShooterItemState::Pickup:
		m_WeaponMesh->SetVisibility(true);
		break;
	case EShooterItemState::PickingUp:
		m_WeaponMesh->SetVisibility(true);
		break;
	case EShooterItemState::PickedUp:
		m_WeaponMesh->SetVisibility(false);
		break;
	case EShooterItemState::Equipped:
		m_WeaponMesh->SetVisibility(true);
		break;
	case EShooterItemState::Failling:
		m_WeaponMesh->SetVisibility(true);
		break;
	}
}

void AShooterWeapon::DecrementAmmo()
{
	int32 AmmoCount = GetAmmo() - 1;

	if (AmmoCount <= 0)
		AmmoCount = 0;

	SetAmmo(AmmoCount);
}

void AShooterWeapon::UpdateMagazineAmmo()
{
	int32 CarriedAmmo = GetMagazineAmmo();

	// Space left in the magazine of weapon
	int32 MagEmptySpace = GetMagazineCapacity() - GetAmmo();

	if (MagEmptySpace > CarriedAmmo)
	{
		ReloadAmmo(CarriedAmmo);
		CarriedAmmo = 0;
	}
	else
	{
		ReloadAmmo(MagEmptySpace);
		CarriedAmmo -= MagEmptySpace;
	}

	SetMagazineAmmo(CarriedAmmo);
}

void AShooterWeapon::ReloadAmmo(int32 AmmoAmount)
{
	checkf(GetAmmo() + AmmoAmount <= GetMagazineCapacity(), TEXT("Attempted to reload with more than magazine capacity"));

	SetAmmo(GetAmmo() + AmmoAmount);
}

void AShooterWeapon::WeaponFalling()
{
	if (EShooterItemState::Failling != GetShooterItemState())
		return;

	FRotator Rotation = FRotator(0.0f, GetCollisionBox()->GetComponentRotation().Yaw, 0.0f);
	GetCollisionBox()->SetWorldRotation(Rotation, false, nullptr, ETeleportType::TeleportPhysics);
}

void AShooterWeapon::FinishFalling()
{
	SetShooterItemState(EShooterItemState::Pickup);
}

void AShooterWeapon::SendBullet()
{
	const USkeletalMeshSocket* Muzzle = GetWeaponMesh()->GetSocketByName(TEXT("Muzzle"));
	if (Muzzle)
	{
		const FTransform MuzzleSocketTrans = Muzzle->GetSocketTransform(GetWeaponMesh());

		if (m_MuzzleFlashParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MuzzleFlashParticle, MuzzleSocketTrans);

		FHitResult BeamHitResult;
		if (GetBeamEndLocation(MuzzleSocketTrans.GetLocation(), BeamHitResult))
		{
			if (IsValid(BeamHitResult.GetActor()))
			{
				// 만약 bullethit 인터페이스를 상속받은 actor를 맞췄다면
				IBulletHit* BulletHitInterface = Cast<IBulletHit>(BeamHitResult.GetActor());
				if (BulletHitInterface)
				{
					BulletHitInterface->BulletHit_Implementation(BeamHitResult);
				}
				else
				{
					if (m_ImpactParticle)
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ImpactParticle, BeamHitResult.Location);
				}

				// 데미지 처리
				AShooterMonster* Monster = Cast<AShooterMonster>(BeamHitResult.GetActor());
				if (IsValid(Monster))
				{
					int32 RandomDamage = FMath::RandRange(-5, 5);
					UGameplayStatics::ApplyDamage(Monster, GetWeaponDamage() + RandomDamage, GetOwnerCharacter()->GetController(), GetOwnerCharacter(), UDamageType::StaticClass());
					Monster->ShowDamageText(GetWeaponDamage() + RandomDamage, BeamHitResult.Location);
				}
			}
		}

		if (IsValid(m_BeamParticleSystem))
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_BeamParticleSystem, MuzzleSocketTrans.GetLocation());
		
			NiagaraComp->SetNiagaraVariableBool(TEXT("User.Trigger"), true);
			NiagaraComp->SetNiagaraVariableVec3(TEXT("User.MuzzlePosition"), MuzzleSocketTrans.GetLocation());
		
			TArray<FVector> ImpactPoints;
			ImpactPoints.Add(BeamHitResult.Location);
			UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(NiagaraComp, TEXT("User.ImpactPositions"), ImpactPoints);
		}
	}
}

bool AShooterWeapon::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult)
{
	FVector OutBeamLocation;
	FHitResult CrosshairHitResult;

	bool bCrosshairHit = GetOwnerCharacter()->TraceUnderCrosshairs(CrosshairHitResult, OutBeamLocation);
	if (bCrosshairHit)
	{
		OutBeamLocation = CrosshairHitResult.Location;
	}
	// Perform a second trace, this time from the gun muzzle
	const FVector FireStart = MuzzleSocketLocation;
	const FVector StartToEnd = OutBeamLocation - MuzzleSocketLocation;
	const FVector FireEnd = FireStart + StartToEnd * 1.1f;

	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(GetOwnerCharacter());

	GetWorld()->LineTraceSingleByChannel(OutHitResult, FireStart, FireEnd, ECollisionChannel::ECC_Visibility, Param);
//
//#if ENABLE_DRAW_DEBUG
//
//	FColor   DrawColor = OutHitResult.bBlockingHit ? FColor::Red : FColor::Green;
//	if (OutHitResult.bBlockingHit)
//		DrawDebugLine(GetWorld(), FireStart, FireEnd, DrawColor, false, 0.1f);
//	else
//		DrawDebugLine(GetWorld(), FireStart, FireEnd, DrawColor, false, 20.f);
//#endif

	if (!OutHitResult.bBlockingHit)
	{
		OutHitResult.Location = OutBeamLocation;
		return false;
	}

	return true;
}

void AShooterWeapon::StartFireTimer()
{
	m_FiringBullet = true;

	GetOwnerCharacter()->SetShooterState(EShooterState::Firing);

	GetWorldTimerManager().SetTimer(m_AutoFireTimer, this, &AShooterWeapon::AutoFireReset, m_AutoFireRate);
}

void AShooterWeapon::AutoFireReset()
{
	m_FiringBullet = false;

	GetOwnerCharacter()->SetShooterState(EShooterState::Unoccupied);

	// 총알이 있으면 연사
	if (HasAmmo())
	{
		if (GetOwnerCharacter()->GetFireButtonPressed())
			WeaponFire();
	}
	// 없으면 재장전
	else
	{
		m_OwnerCharacter->WeaponReload();
	}
}

void AShooterWeapon::PlayFireSound()
{
	if (IsValid(m_FireSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_FireSound, GetActorLocation());
	}
}

void AShooterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WeaponFalling();
}

void AShooterWeapon::WeaponFire()
{
	if (HasAmmo())
	{
		SendBullet();
		DecrementAmmo();

		StartFireTimer();
		PlayFireSound();
	}
}

bool AShooterWeapon::HasAmmo()
{
	return GetAmmo() > 0;
}

bool AShooterWeapon::HasCarryingAmmo()
{
	return GetMagazineAmmo() > 0;
}

bool AShooterWeapon::IsClipFull()
{
	return GetAmmo() >= GetMagazineCapacity();
}

bool AShooterWeapon::PickupAmmo()
{


	return true;
}

bool AShooterWeapon::IsFiring()
{
	return m_FiringBullet;
}

void AShooterWeapon::WeaponReload()
{
	if (HasCarryingAmmo())
	{
		UpdateMagazineAmmo();
	}
}

void AShooterWeapon::AddAmmo(AShooterAmmo* InAmmo)
{
	int32 AddingAmmo = InAmmo->GetAmmo();
	if (AddingAmmo < GetMagazineCapacity())
	{
		AddingAmmo = GetMagazineCapacity() * 2;
	}

	SetMagazineAmmo(GetMagazineAmmo() + AddingAmmo);
}

void AShooterWeapon::DropWeapon()
{
	FDetachmentTransformRules DetachmentTransfromRules(EDetachmentRule::KeepWorld, true);
	GetCollisionBox()->DetachFromComponent(DetachmentTransfromRules);

	SetShooterItemState(EShooterItemState::Failling);

	m_OwnerCharacter->GetShooterOverlayWidget()->SetSlotEmpty(m_InventoryIndex);
	SetOwnerCharacter(nullptr);
	SetInventoryIndex(INDEX_NONE);

	Destroy();

	//FRotator Rotation = FRotator(0.0f, GetCollisionBox()->GetComponentRotation().Yaw, 0.0f);
	//GetCollisionBox()->SetWorldRotation(Rotation, false, nullptr, ETeleportType::TeleportPhysics);

	//const FVector Forward = GetCollisionBox()->GetForwardVector();
	//const FVector Right = GetCollisionBox()->GetRightVector();
	//// Direction in which we throw weapon
	//FVector ImpulseDirection = Right.RotateAngleAxis(-20.0f, Forward);

	//float RandomRotation = FMath::FRandRange(-20.0f, 20.0f);
	//ImpulseDirection = ImpulseDirection.RotateAngleAxis(RandomRotation, FVector(0.0f, 0.0f, 1.0f));
	//ImpulseDirection *= 7'000.0f;
	//GetCollisionBox()->AddImpulse(ImpulseDirection);

	//GetWorldTimerManager().SetTimer(m_ItemDropTimer, this, &ThisClass::FinishItemDrop, m_ItemDropTime);
}

//void AShooterWeapon::DropItem()
//{
//	SetShooterItemState(EShooterItemState::Failling);
//
//	GetCollisionBox()->AddVelocityChangeImpulseAtLocation(GetActorUpVector() * 250.0f, GetActorLocation());
//
//	GetWorldTimerManager().SetTimer(m_ItemDropTimer, this, &ThisClass::FinishItemDrop, m_ItemDropTime);
//}

int32 AShooterWeapon::SetAmmo(int32 InAmmo)
{
	m_Ammo = InAmmo;

	m_OwnerCharacter->GetShooterOverlayWidget()->SetCrosshairAmmoCurrent(m_Ammo);
	m_OwnerCharacter->GetShooterOverlayWidget()->SetDisplayAmmoCurrent(m_Ammo);

	return m_Ammo;
}

int32 AShooterWeapon::SetMagazineAmmo(int32 InAmmo)
{
	m_MagazineAmmo = InAmmo;

	m_OwnerCharacter->GetShooterOverlayWidget()->SetDisplayAmmoMagazine(m_MagazineAmmo);

	return m_MagazineAmmo;
}

bool AShooterWeapon::SetMovingClip(bool Move)
{
	m_MovingClip = Move;

	return m_MovingClip;
}

int32 AShooterWeapon::SetInventoryIndex(int32 InIndex)
{
	m_InventoryIndex = InIndex;

	return m_InventoryIndex;
}
