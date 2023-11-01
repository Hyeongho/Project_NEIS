// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_GameMode.h"
#include "../Player/BHG_Player.h"
#include "../SpawnObject/DefaultSpawnObject.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "../UI/BHGDefaultUserWidget.h"
#include "../../Player/DefaultPlayerState.h"
#include "../Player/BHG_PlayerController.h"
#include "../UI/BHGSkillUI.h"
#include "../Portal/PortalObject.h"
#include "../SoundPlayer/SoundPlayer.h"
#include "../UI/BossHpWidget.h"

ABHG_GameMode::ABHG_GameMode()
	: Super()
{
	DefaultPawnClass = ABHG_Player::StaticClass();

	BossSpawn = false;

	BossEnd = false;

	UIEnable = true;	

	PortalTime = 0.f;
}

void ABHG_GameMode::BossStart()
{

	GetWorld()->SpawnActor<ADefaultSpawnObject>(m_BossSpawnObject, FVector(1000.0, -250.0, -180.0), FRotator::ZeroRotator);

	BossSpawn = true;

	mMainWidget->SetVisibility(ESlateVisibility::Hidden);
	mSkillUIWidget->SetVisibility(ESlateVisibility::Hidden);

	UIEnable = false;

	m_BGMPlayer->PauseSound();

}

void ABHG_GameMode::PlayerAttack()
{
	if (IsValid(mSkillUIWidget))
		mSkillUIWidget->DefaultAttackImageOpacity();
}

void ABHG_GameMode::PortalStart()
{
	BossEnd = true;
}

void ABHG_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABHG_GameMode::InitGameState()
{
	Super::InitGameState();
}

void ABHG_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ABHG_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(this, 0)->GetPlayerState<ADefaultPlayerState>()->InitPlayerData(FName("YIn"));

	if (IsValid(mMainUIClass))
	{
		mMainWidget = CreateWidget<UBHGDefaultUserWidget>(GetWorld(), mMainUIClass);

		if (IsValid(mMainWidget))
			mMainWidget->AddToViewport();
	}


	if (IsValid(mSkillUIClass))
	{
		mSkillUIWidget = CreateWidget<UBHGSkillUI>(GetWorld(), mSkillUIClass);

		if (IsValid(mSkillUIWidget))
			mSkillUIWidget->AddToViewport();
	}

	if (IsValid(m_BGMPlayerClass))
	{
		m_BGMPlayer = GetWorld()->SpawnActor<ASoundPlayer>(m_BGMPlayerClass, FVector(0.0, 0.0, 0.0), FRotator::ZeroRotator);
	}

}

void ABHG_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!UIEnable)
	{
		UIVisiableTime += DeltaTime;

		if (UIVisiableTime > 6.5f)
		{
			m_BGMPlayer->ChangeSound();

			mMainWidget->SetVisibility(ESlateVisibility::Visible);
			mSkillUIWidget->SetVisibility(ESlateVisibility::Visible);

			UIVisiableTime = 0.f;
			UIEnable = true;

			if (IsValid(m_BossHPUIClass))
			{
				m_BossHPUIWidget = CreateWidget<UBossHpWidget>(GetWorld(), m_BossHPUIClass);

				if(IsValid(m_BossHPUIWidget))
					m_BossHPUIWidget->AddToViewport();
			}

		}
	}

	if (BossEnd)
	{
		PortalTime += DeltaTime;

		if (PortalTime > 4.f)
		{
			if (IsValid(m_PortalObject))
			{
				GetWorld()->SpawnActor<APortalObject>(m_PortalObject, FVector(1560.0, -180.0, -20.0), FRotator::ZeroRotator);
				PortalTime = 0.f;
				BossEnd = false;
			}
			

		}
	}

}
