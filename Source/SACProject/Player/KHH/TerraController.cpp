// Fill out your copyright notice in the Description page of Project Settings.


#include "TerraController.h"
#include "TerraCharacter.h"
#include "TerraAnimInstance.h"
#include "../DefaultPlayerState.h"

ATerraController::ATerraController()
{
	PrimaryActorTick.bCanEverTick = true;

	m_IsInput = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KHH/Player/Input/IMC_Terra.IMC_Terra'"));

	if (DefaultContext.Succeeded())
	{
		m_DefaultContext = DefaultContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveAction(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraMove.IA_TerraMove'"));

	if (MoveAction.Succeeded())
	{
		m_MoveAction = MoveAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraRotation(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraRotation.IA_TerraRotation'"));

	if (TerraRotation.Succeeded())
	{
		m_TerraRotation = TerraRotation.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraAttack(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraAttack.IA_TerraAttack'"));

	if (TerraAttack.Succeeded())
	{
		m_TerraAttack = TerraAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraGurad(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraGurad.IA_TerraGurad'"));

	if (TerraAttack.Succeeded())
	{
		m_TerraGurad = TerraGurad.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraSkillQ(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraSkillQ.IA_TerraSkillQ'"));

	if (TerraAttack.Succeeded())
	{
		m_TerraSkillQ = TerraSkillQ.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraSkillE(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraSkillE.IA_TerraSkillE'"));

	if (TerraAttack.Succeeded())
	{
		m_TerraSkillE = TerraSkillE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TerraSkillR(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/Player/Input/IA_TerraSkillR.IA_TerraSkillR'"));

	if (TerraAttack.Succeeded())
	{
		m_TerraSkillR = TerraSkillR.Object;
	}
}

void ATerraController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ATerraController::BeginPlay()
{
	Super::BeginPlay();

	m_Anim = Cast<UTerraAnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());
}

void ATerraController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATerraController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ATerraController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATerraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(m_DefaultContext, 0);
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &ATerraController::Move);
	Input->BindAction(m_TerraRotation, ETriggerEvent::Triggered, this, &ATerraController::TerraRotation);
	Input->BindAction(m_TerraAttack, ETriggerEvent::Triggered, this, &ATerraController::Attack);
	Input->BindAction(m_TerraGurad, ETriggerEvent::Started, this, &ATerraController::Gurad);
	Input->BindAction(m_TerraGurad, ETriggerEvent::Completed, this, &ATerraController::ReleaseGurad);
	Input->BindAction(m_TerraSkillQ, ETriggerEvent::Triggered, this, &ATerraController::SkillQ);
	Input->BindAction(m_TerraSkillE, ETriggerEvent::Triggered, this, &ATerraController::SkillE);
	Input->BindAction(m_TerraSkillR, ETriggerEvent::Triggered, this, &ATerraController::SkillR);
}

void ATerraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerraController::Move(const FInputActionValue& Value)
{
	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void ATerraController::Jump(const FInputActionValue& Value)
{
}

void ATerraController::TerraRotation(const FInputActionValue& Value)
{
	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	GetCharacter()->AddControllerYawInput(MovementVector.X);
}

void ATerraController::Attack(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	m_Anim->Attack();
}

void ATerraController::Gurad(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	ATerraCharacter* Terra = Cast<ATerraCharacter>(GetPawn());

	Terra->SetTerraType(ETerraType::Gurad);

	m_Anim->GuradIntro();
}

void ATerraController::ReleaseGurad(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	ATerraCharacter* Terra = Cast<ATerraCharacter>(GetPawn());

	Terra->SetTerraType(ETerraType::Default);

	m_Anim->ChangeAnim(ETerraAnimType::Default);
}

void ATerraController::SkillQ(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	ATerraCharacter* Terra = Cast<ATerraCharacter>(GetPawn());

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(Terra->GetPlayerState());

	if (IsValid(DefaultPlayerState))
	{
		int32 MP = DefaultPlayerState->GetMP();

		if (MP >= 20)
		{
			m_Anim->Skill(0);

			DefaultPlayerState->AddMP(-20);
		}
	}
}

void ATerraController::SkillE(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	ATerraCharacter* Terra = Cast<ATerraCharacter>(GetPawn());

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(Terra->GetPlayerState());

	if (IsValid(DefaultPlayerState))
	{
		int32 MP = DefaultPlayerState->GetMP();

		if (MP >= 50)
		{
			m_Anim->Skill(1);

			DefaultPlayerState->AddMP(-50);
		}
	}
}

void ATerraController::SkillR(const FInputActionValue& Value)
{
	if (!m_IsInput)
	{
		return;
	}

	if (m_Anim->GetAnimType() == ETerraAnimType::Skill)
	{
		return;
	}

	ATerraCharacter* Terra = Cast<ATerraCharacter>(GetPawn());

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(Terra->GetPlayerState());

	if (IsValid(DefaultPlayerState))
	{
		int32 MP = DefaultPlayerState->GetMP();

		if (MP >= 100)
		{
			m_Anim->Skill(2);

			DefaultPlayerState->AddMP(-100);
		}
	}
}
