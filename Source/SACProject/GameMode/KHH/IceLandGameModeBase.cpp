// Fill out your copyright notice in the Description page of Project Settings.


#include "IceLandGameModeBase.h"
#include "../../DefaultGameInstance.h"
#include "../../Player/KHH/TerraCharacter.h"
#include "../../Player/KHH/TerraController.h"
#include "../../UI/KHH/FrozenCaveWidget.h"
#include "../../Player/DefaultPlayerState.h"

AIceLandGameModeBase::AIceLandGameModeBase()
{
	DefaultPawnClass = ATerraCharacter::StaticClass();

	PlayerControllerClass = ATerraController::StaticClass();

	PlayerStateClass = ADefaultPlayerState::StaticClass();

	m_IsFadeOut = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> FrozenCaveWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/FrozenCaveWidget.FrozenCaveWidget_C'"));

	if (FrozenCaveWidgetClass.Succeeded())
	{
		m_FrozenCaveWidgetClass = FrozenCaveWidgetClass.Class;
	}
}

void AIceLandGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AIceLandGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AIceLandGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AIceLandGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(this, 0)->GetPlayerState<ADefaultPlayerState>()->InitPlayerData(FName("Terra"));

	if (IsValid(m_FrozenCaveWidgetClass))
	{
		m_FrozenCaveWidget = CreateWidget<UFrozenCaveWidget>(GetWorld(), m_FrozenCaveWidgetClass);

		if (IsValid(m_FrozenCaveWidget))
		{
			m_FrozenCaveWidget->AddToViewport();
		}
	}
}

void AIceLandGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
