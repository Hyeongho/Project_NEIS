// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "../../DefaultGameInstance.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "../../Player/CJH/ShooterPlayerController.h"
#include "../../Player/DefaultPlayerState.h"
#include "../../UI/CJH/ShooterOverlayWidget.h"

AShooterGameMode::AShooterGameMode()
	: Super()
	, m_IsStart(false)
	, m_CurrentScore(0)
	, m_WinScore(20)
	, m_Clear(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = AShooterCharacter::StaticClass();

	PlayerControllerClass = AShooterPlayerController::StaticClass();

	PlayerStateClass = ADefaultPlayerState::StaticClass();
}

void AShooterGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AShooterGameMode::InitGameState()
{
	Super::InitGameState();
}

void AShooterGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	m_ShooterPC = Cast<AShooterPlayerController>(NewPlayer);
}

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_ShooterPC))
	{
		m_ShooterPC->GetPlayerState<ADefaultPlayerState>()->InitPlayerData(FName("LtBelica"));
	}
}

void AShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_IsStart)
	{
		if (IsValid(m_ShooterPC))
		{
			m_ShooterPC->GetShooterOverlayWidget()->SetCurrentScoreText(m_CurrentScore);
			m_ShooterPC->GetShooterOverlayWidget()->SetMaxScoreText(m_WinScore);

			m_IsStart = true;
		}
	}
}

void AShooterGameMode::AddScore()
{
	if (!m_Clear)
	{
		++m_CurrentScore;

		if (IsValid(m_ShooterPC))
		{
			m_ShooterPC->GetShooterOverlayWidget()->SetCurrentScoreText(m_CurrentScore);
			m_ShooterPC->GetShooterOverlayWidget()->PlayCurrentScoreAnim();
		}

		if (m_CurrentScore >= m_WinScore)
			ClearShooterMode();
	}
}

void AShooterGameMode::ClearShooterMode()
{
	m_Clear = true;
}
