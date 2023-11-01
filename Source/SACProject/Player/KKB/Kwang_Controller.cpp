// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_Controller.h"
#include "Kwang_AnimInstance.h"
#include "Kwang_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AKwang_Controller::AKwang_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IMC_Kwang.IMC_Kwang'"));

	if (DefaultContext.Succeeded())
		m_DefaultContext = DefaultContext.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> AttackAction(TEXT("/Script/EnhancedInput.InputAction'/Game/KKB/Player/Input/IA_Kwang_Attack.IA_Kwang_Attack'"));

	if (AttackAction.Succeeded())
		m_AttackAction = AttackAction.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> DashAction(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Dash.IA_Kwang_Dash'"));

	if (DashAction.Succeeded())
		m_DashAction = DashAction.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> MoveAction(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Move.IA_Kwang_Move'"));

	if (MoveAction.Succeeded())
		m_MoveAction = MoveAction.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> Rotation(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Rotation.IA_Kwang_Rotation'"));

	if (Rotation.Succeeded())
		m_Rotation = Rotation.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> Skill1Action(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Skill1.IA_Kwang_Skill1'"));

	if (Skill1Action.Succeeded())
		m_Skill1Action = Skill1Action.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> Skill2Action(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Skill2.IA_Kwang_Skill2'"));

	if (Skill2Action.Succeeded())
		m_Skill2Action = Skill2Action.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> Skill3Action(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KKB/Player/Input/IA_Kwang_Skill3.IA_Kwang_Skill3'"));

	if (Skill3Action.Succeeded())
		m_Skill3Action = Skill3Action.Object;



	m_MovePossible = true;
}

void AKwang_Controller::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AKwang_Controller::BeginPlay()
{
	Super::BeginPlay();

	// 마우스 커서를 보이게 설정
	SetShowMouseCursor(true);
}

void AKwang_Controller::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AKwang_Controller::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AKwang_Controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void AKwang_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(m_DefaultContext, 0);
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(m_AttackAction, ETriggerEvent::Triggered, this, &AKwang_Controller::AttackAction);
	Input->BindAction(m_DashAction, ETriggerEvent::Triggered, this, &AKwang_Controller::DashAction);
	Input->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AKwang_Controller::MoveAction);
	Input->BindAction(m_Rotation, ETriggerEvent::None, this, &AKwang_Controller::RotationCharacter);
	Input->BindAction(m_Skill1Action, ETriggerEvent::Started, this, &AKwang_Controller::Skill1Action);
	Input->BindAction(m_Skill1Action, ETriggerEvent::Completed, this, &AKwang_Controller::Skill1ReleaseAction);
	Input->BindAction(m_Skill2Action, ETriggerEvent::Started, this, &AKwang_Controller::Skill2Action);
	Input->BindAction(m_Skill3Action, ETriggerEvent::Started, this, &AKwang_Controller::Skill3Action);
}

void AKwang_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKwang_Controller::AttackAction(const FInputActionValue& Value)
{
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());

	Anim->Attack();
}

void AKwang_Controller::DashAction(const FInputActionValue& Value)
{
	GetPlayerCharacter()->Dash();
}

void AKwang_Controller::MoveAction(const FInputActionValue& Value)
{
	if (!m_MovePossible)
		return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void AKwang_Controller::RotationCharacter(const FInputActionValue& Value)
{
	if (!m_MovePossible)
		return;

	float LocationX, LocationY;
	GetMousePosition(LocationX, LocationY);

	FVector2D MousePos(LocationX, LocationY);

	FHitResult HitResult;

	if (GetHitResultAtScreenPosition(MousePos, ECC_Visibility, true, HitResult)) {
		FVector TargetLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);
		TargetLocation.Z = GetCharacter()->GetActorLocation().Z;


		FVector Dir = (TargetLocation - GetCharacter()->GetActorLocation()).GetSafeNormal();

		GetCharacter()->GetMesh()->SetWorldRotation(FRotator(0.0, Dir.Rotation().Yaw - 90.0, 0.0));

		//UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());

		//FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), TargetLocation);
		//FRotator Rotator = FRotator(GetCharacter()->GetActorRotation().Pitch, (LookAtRotator.Yaw - 90.0), GetCharacter()->GetActorRotation().Roll);
		//GetCharacter()->GetMesh()->SetWorldRotation(Rotator);
	}
}

void AKwang_Controller::Skill1Action(const FInputActionValue& Value)
{
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill1();
}

void AKwang_Controller::Skill1ReleaseAction(const FInputActionValue& Value)
{
	//Skill1Release();
	GetPlayerCharacter()->Skill1_ChargeShot();
}

void AKwang_Controller::Skill2Action(const FInputActionValue& Value)
{
	GetPlayerCharacter()->Skill2_ThunderStorm();
}

void AKwang_Controller::Skill3Action(const FInputActionValue& Value)
{
	GetPlayerCharacter()->Skill3_ThunderAura();
}

void AKwang_Controller::Skill1Release()
{
	UKwang_AnimInstance* Anim = Cast<UKwang_AnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
		Anim->Skill1Release();
}

AKwang_PlayerCharacter* AKwang_Controller::GetPlayerCharacter() const
{
	return CastChecked<AKwang_PlayerCharacter>(K2_GetPawn());
}
