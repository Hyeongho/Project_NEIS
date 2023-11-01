// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SACProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ASACProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASACProjectGameModeBase();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;
};
