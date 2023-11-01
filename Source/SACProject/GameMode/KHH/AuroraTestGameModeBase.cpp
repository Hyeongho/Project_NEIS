// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraTestGameModeBase.h"
#include "../../AI/KHH/AuroraAICharacter.h"
#include "../../AI/KHH/Input/AuroraTestController.h"

AAuroraTestGameModeBase::AAuroraTestGameModeBase()
{
	DefaultPawnClass = AAuroraAICharacter::StaticClass();

	PlayerControllerClass = AAuroraTestController::StaticClass();
}

void AAuroraTestGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AAuroraTestGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AAuroraTestGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AAuroraTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuroraTestGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
