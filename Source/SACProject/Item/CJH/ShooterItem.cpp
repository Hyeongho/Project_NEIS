// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterItem.h"
#include "Components/SphereComponent.h"
#include "../../Player/CJH/ShooterCharacter.h"

AShooterItem::AShooterItem()
	: Super()
	, m_ShooterItemState(EShooterItemState::Pickup)
	, m_ShooterItemType(EShooterItemType::MAX)
	, m_ZCurveTime(0.7f)
	, m_ItemInterpX(0.0f)
	, m_ItemInterpY(0.0f)
	, m_InterpInitialYawOffset(0.0f)
	, m_ItemInterpStartLocation(FVector(0.0f))
	, m_ItemDropTime(0.1f)
{
	m_ItemName = TEXT("ShooterItem");

	//m_AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	//m_AreaSphere->SetSphereRadius(500.0f);
	//m_AreaSphere->SetupAttachment(GetRootComponent());
}

void AShooterItem::BeginPlay()
{
	Super::BeginPlay();


	// Setup overlap for CollisionBox
	GetCollisionBox()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	GetCollisionBox()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
	GetCollisionBox()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollisionBoxHit);

	// Setup overlap for AreaSphere
	//m_AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AShooterItem::OnAreaSphereBeginOverlap);
	//m_AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AShooterItem::OnAreaSphereEndOverlap);

	SetItemProperties(m_ShooterItemState);
}

void AShooterItem::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnCollisionBoxBeginOverlap"));

	if (OtherActor)
	{
		AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);
		if (Character)
		{
			PickedUp(Character);
		}
	}
}

void AShooterItem::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnCollisionBoxEndOverlap"));
}

void AShooterItem::OnCollisionBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCollisionBoxHit"));

	SetShooterItemState(EShooterItemState::Pickup);
}

//void AShooterItem::OnAreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OnAreaSphereBeginOverlap"));
//}
//
//void AShooterItem::OnAreaSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OnAreaSphereEndOverlap"));
//}

void AShooterItem::SetItemProperties(EShooterItemState InState)
{
	switch (InState)
	{
	case EShooterItemState::Pickup:
		// ItemMesh
		m_ItemMesh->SetVisibility(true);
		m_CollisionBox->SetCollisionProfileName("Item");
		m_CollisionBox->SetEnableGravity(false);
		m_CollisionBox->SetSimulatePhysics(false);
		break;
	case EShooterItemState::PickingUp:
		m_ItemMesh->SetVisibility(true);
		m_CollisionBox->SetCollisionProfileName("NoCollision");
		m_CollisionBox->SetEnableGravity(false);
		m_CollisionBox->SetSimulatePhysics(false);

		PlayPickupSound();
		break;
	case EShooterItemState::PickedUp:
		m_ItemMesh->SetVisibility(false);
		m_CollisionBox->SetCollisionProfileName("NoCollision");
		m_CollisionBox->SetEnableGravity(false);
		m_CollisionBox->SetSimulatePhysics(false);

		PlayPickedUpSound();
		break;
	case EShooterItemState::Equipped:
		m_ItemMesh->SetVisibility(true);
		m_CollisionBox->SetCollisionProfileName("NoCollision");
		m_CollisionBox->SetEnableGravity(false);
		m_CollisionBox->SetSimulatePhysics(false);
		break;
	case EShooterItemState::Failling:
		m_ItemMesh->SetVisibility(true);
		m_CollisionBox->SetCollisionProfileName("NoCollision");
		m_CollisionBox->SetEnableGravity(true);
		m_CollisionBox->SetSimulatePhysics(true);
		break;
	}
}

void AShooterItem::PickedUp(AShooterCharacter* InCharacter)
{
	if (!IsValid(InCharacter))
		return;

	SetOwnerCharacter(InCharacter);

	StartItemZCurve();
}

void AShooterItem::StartItemZCurve()
{
	SetShooterItemState(EShooterItemState::PickingUp);

	m_ItemInterpStartLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(m_ItemInterpTimer, this, &AShooterItem::FinishItemZCurve, m_ZCurveTime);

	const float CameraRotationYaw = GetOwnerCharacter()->GetCamera()->GetComponentRotation().Yaw;
	const float ItemRotationYaw = GetActorRotation().Yaw;

	m_InterpInitialYawOffset = ItemRotationYaw - CameraRotationYaw;
}

void AShooterItem::FinishItemZCurve()
{
	if (IsValid(m_OwnerCharacter))
	{
		SetShooterItemState(EShooterItemState::PickedUp);
		
		m_OwnerCharacter->GetPickupItem(this);
	}

	OnFinishItemZCurve();

	// 아이템 크기 원상복귀
	SetActorScale3D(FVector(1.0f));
}

void AShooterItem::OnFinishItemZCurve()
{
}

void AShooterItem::ItemInterp(float DeltaTime)
{
	if (EShooterItemState::PickingUp != m_ShooterItemState)
		return;

	if (!IsValid(m_OwnerCharacter))
		return;

	if (IsValid(m_ItemZCurve))
	{
		// Elapsed time since we started ItemInterpTimer
		const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(m_ItemInterpTimer);
		// Get curve value corresponding to ElapsedTime
		const float CuverValue = m_ItemZCurve->GetFloatValue(ElapsedTime);

		// Get the item's initial location when the curve started
		FVector ItemLocation = m_ItemInterpStartLocation;
		const FVector CameraInterpLocation = m_OwnerCharacter->GetCameraInterpLocation();

		// Vector from Item to Camera interp location, X and Y are zeroed out
		const FVector ItemToCamera = FVector(0.0f, 0.0f, (CameraInterpLocation - ItemLocation).Z);
		// Scale factor to multiply with curve value;
		const float DeltaZ = ItemToCamera.Size();

		const FVector CurrentLocation = GetActorLocation();
		const float InterpXValue = FMath::FInterpTo(CurrentLocation.X, CameraInterpLocation.X, DeltaTime, 30.0f);
		const float InterpYValue = FMath::FInterpTo(CurrentLocation.Y, CameraInterpLocation.Y, DeltaTime, 30.0f);

		ItemLocation.X = InterpXValue;
		ItemLocation.Y = InterpYValue;

		// Adding curve value to the Z component of the initial location (scaled by DeltaZ)
		ItemLocation.Z += CuverValue * DeltaZ;
		SetActorLocation(ItemLocation, true, nullptr, ETeleportType::TeleportPhysics);

		const FRotator CameraRotation = m_OwnerCharacter->GetCamera()->GetComponentRotation();
		FRotator ItemRotation = FRotator(0.0f, CameraRotation.Yaw + m_InterpInitialYawOffset, 0.0f);
		SetActorRotation(ItemRotation, ETeleportType::TeleportPhysics);

		if (IsValid(m_ItemScaleCurve))
		{
			const float ScaleCuverValue = m_ItemScaleCurve->GetFloatValue(ElapsedTime);
			SetActorScale3D(FVector(ScaleCuverValue));
		}
	}
}

void AShooterItem::PlayPickupSound()
{
	if (!IsValid(m_OwnerCharacter))
		return;

	if (IsValid(GetPickupSound()))
		UGameplayStatics::PlaySound2D(this, GetPickupSound());
}

void AShooterItem::PlayPickedUpSound()
{
	if (!IsValid(m_OwnerCharacter))
		return;

	if (IsValid(GetPickedUpSound()))
		UGameplayStatics::PlaySound2D(this, GetPickedUpSound());
}

void AShooterItem::FinishItemDrop()
{
	SetShooterItemState(EShooterItemState::Pickup);
}

void AShooterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ItemInterp(DeltaTime);
}

void AShooterItem::DropItem()
{
	SetShooterItemState(EShooterItemState::Pickup);

	//GetCollisionBox()->AddVelocityChangeImpulseAtLocation(GetActorUpVector() * 250.0f, GetActorLocation());

	//GetWorldTimerManager().SetTimer(m_ItemDropTimer, this, &ThisClass::FinishItemDrop, m_ItemDropTime);
}

void AShooterItem::SetOwnerCharacter(AShooterCharacter* InCharacter)
{
	m_OwnerCharacter = InCharacter;
}

void AShooterItem::SetShooterItemState(EShooterItemState InState)
{
	m_ShooterItemState = InState;

	SetItemProperties(InState);
}

void AShooterItem::SetShooterItemType(EShooterItemType InType)
{
	m_ShooterItemType = InType;
}
