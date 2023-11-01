// Copyright Epic Games, Inc. All Rights Reserved.


#include "SACProjectGameModeBase.h"

ASACProjectGameModeBase::ASACProjectGameModeBase()
{
}

void ASACProjectGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ASACProjectGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void ASACProjectGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ASACProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASACProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
