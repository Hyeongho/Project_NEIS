// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraTestController.h"
#include "../AuroraAICharacter.h"
#include "../AuroraAIAnimInstance.h"

AAuroraTestController::AAuroraTestController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KHH/AI/Input/IMC_Aurora.IMC_Aurora'"));

	if (DefaultContext.Succeeded())
	{
		m_DefaultContext = DefaultContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DassAction(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/AI/Input/IA_AuroraDass.IA_AuroraDass'"));

	if (DassAction.Succeeded())
	{
		m_DassAction = DassAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> FreezeAction(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/AI/Input/IA_AuraraFreeze.IA_AuraraFreeze'"));

	if (FreezeAction.Succeeded())
	{
		m_FreezeAction = FreezeAction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> UltimateAction(TEXT("/Script/EnhancedInput.InputAction'/Game/KHH/AI/Input/IA_AuroraUltimate.IA_AuroraUltimate'"));

	if (UltimateAction.Succeeded())
	{
		m_UltimateAction = UltimateAction.Object;
	}
}

void AAuroraTestController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAuroraTestController::BeginPlay()
{
	Super::BeginPlay();

	m_Anim = Cast<UAuroraAIAnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());
}

void AAuroraTestController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAuroraTestController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AAuroraTestController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AAuroraTestController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(m_DefaultContext, 0);
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	Input->BindAction(m_DassAction, ETriggerEvent::Triggered, this, &AAuroraTestController::Dass);
	Input->BindAction(m_FreezeAction, ETriggerEvent::Triggered, this, &AAuroraTestController::Freeze);
	Input->BindAction(m_UltimateAction, ETriggerEvent::Triggered, this, &AAuroraTestController::Ultimate);
}

void AAuroraTestController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAuroraTestController::Dass(const FInputActionValue& Value)
{
	m_Anim->Skill(0);
}

void AAuroraTestController::Freeze(const FInputActionValue& Value)
{
	m_Anim->Skill(1);
}

void AAuroraTestController::Ultimate(const FInputActionValue& Value)
{
	m_Anim->Skill(2);
}
