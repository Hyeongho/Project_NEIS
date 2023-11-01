// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"

UDefaultGameInstance::UDefaultGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTable(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'"));

	if (PlayerTable.Succeeded())
	{
		m_PlayerDataTable = PlayerTable.Object;
	}
}

void UDefaultGameInstance::Init()
{
	Super::Init();
}

const FPlayerDataTable* UDefaultGameInstance::FindPlayerData(const FName& Name)
{
	return m_PlayerDataTable->FindRow<FPlayerDataTable>(Name, TEXT(""));
}

void UDefaultGameInstance::SetPlayerCharacter(APlayerCharacter* InCharacter)
{
	m_PlayerCharacter = InCharacter;
}
