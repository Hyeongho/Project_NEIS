// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "KwangTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AKwangTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKwangTestGameMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

	
};
