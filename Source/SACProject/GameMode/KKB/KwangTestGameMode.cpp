// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangTestGameMode.h"
#include "../../Player/KKB/Kwang_PlayerCharacter.h"
#include "../../Player/KKB/Kwang_Controller.h"

AKwangTestGameMode::AKwangTestGameMode()
{
	DefaultPawnClass = AKwang_PlayerCharacter::StaticClass();

	PlayerControllerClass = AKwang_Controller::StaticClass();
}

void AKwangTestGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AKwangTestGameMode::InitGameState()
{
	Super::InitGameState();
}

void AKwangTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AKwangTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AKwangTestGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
