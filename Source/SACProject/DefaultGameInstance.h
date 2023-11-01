// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "DefaultGameInstance.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class SACPROJECT_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDefaultGameInstance();

private:
	TObjectPtr<UDataTable> m_PlayerDataTable;

	TObjectPtr<APlayerCharacter> m_PlayerCharacter;

public:
	virtual void Init();

public:
	const FPlayerDataTable* FindPlayerData(const FName& Name);

	void SetPlayerCharacter(APlayerCharacter* InCharacter);

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetPlayerCharacter() const { return m_PlayerCharacter; }
	
};
