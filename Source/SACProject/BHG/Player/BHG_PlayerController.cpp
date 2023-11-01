// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_PlayerController.h"
#include "BHG_Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"


ABHG_PlayerController::ABHG_PlayerController()
	: Super()
{
	
}

void ABHG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* eInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (eInputComponent)
	{
		// bind action
		if (IsValid(m_MoveIA))
			eInputComponent->BindAction(m_MoveIA, ETriggerEvent::Triggered, this, &ABHG_PlayerController::MoveAction);

		if (IsValid(m_MouseIA))
			eInputComponent->BindAction(m_MouseIA, ETriggerEvent::None, this, &ABHG_PlayerController::RotationCharacterAction);

		if (IsValid(m_MouseLeftClickIA))		
			eInputComponent->BindAction(m_MouseLeftClickIA, ETriggerEvent::Started, this, &ABHG_PlayerController::MouseLeftClickAction);

		if (IsValid(m_MouseRightClickIA))
			eInputComponent->BindAction(m_MouseRightClickIA, ETriggerEvent::Started, this, &ABHG_PlayerController::MouseRightClickAction);

		if (IsValid(m_QButtonIA))
			eInputComponent->BindAction(m_QButtonIA, ETriggerEvent::Started, this, &ABHG_PlayerController::QKeyAction);

		if (IsValid(m_EButtonIA))
			eInputComponent->BindAction(m_EButtonIA, ETriggerEvent::Started, this, &ABHG_PlayerController::EKeyAction);

		if (IsValid(m_Num1ButtonIA))
			eInputComponent->BindAction(m_Num1ButtonIA, ETriggerEvent::Started, this, &ABHG_PlayerController::Num1KeyAction);

		if (IsValid(m_Num2ButtonIA))
			eInputComponent->BindAction(m_Num2ButtonIA, ETriggerEvent::Started, this, &ABHG_PlayerController::Num2KeyAction);

		if (IsValid(m_SpaceKeyIA))
			eInputComponent->BindAction(m_SpaceKeyIA, ETriggerEvent::Started, this, &ABHG_PlayerController::SpaceKeyAction);
		
	}


}

void ABHG_PlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABHG_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//bShowMouseCursor = true;

	SetShowMouseCursor(true);

	UEnhancedInputLocalPlayerSubsystem* eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (eiSubsystem)
	{
		eiSubsystem->ClearAllMappings();
		eiSubsystem->AddMappingContext(m_YinIMC, 0);
	}
}

void ABHG_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABHG_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABHG_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABHG_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABHG_PlayerController::MoveAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->MoveAxis(Value);
}

void ABHG_PlayerController::RotationCharacterAction(const FInputActionValue& Value)
{
	float LocationX, LocationY;
	GetMousePosition(LocationX, LocationY);

	FVector2D MousePos(LocationX, LocationY);

	FHitResult HitResult;

	if (GetHitResultAtScreenPosition(MousePos, ECC_Visibility, true, HitResult)) {
		FVector TargetLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);

		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), TargetLocation);

		// 보간된 회전값 계산
		FRotator Rotator = FMath::RInterpTo(GetCharacter()->GetActorRotation(), LookAtRotator, GetWorld()->DeltaTimeSeconds, 5.f);

		Rotator.Roll = 0.f;
		Rotator.Pitch = 0.f;

		GetCharacter()->SetActorRotation(Rotator);
	}

}

void ABHG_PlayerController::MouseLeftClickAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->DefaultAttackKey();
}

void ABHG_PlayerController::MouseRightClickAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->ShurikenAttackkey();
}

void ABHG_PlayerController::QKeyAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->NightmareKey();
}

void ABHG_PlayerController::EKeyAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->CounterAttackKey();
}

void ABHG_PlayerController::Num1KeyAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->ShadowPartnerKey();
}

void ABHG_PlayerController::Num2KeyAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->UltimateKey();
}

void ABHG_PlayerController::SpaceKeyAction(const FInputActionValue& Value)
{
	ABHG_Player* OwnerCharacter = Cast<ABHG_Player>(GetPawn());

	if (IsValid(OwnerCharacter))
		OwnerCharacter->EvadeKey();
	
}


