// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class AShooterPlayerController;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddScore();

protected:
	void ClearShooterMode();

protected:
	TObjectPtr<AShooterPlayerController> m_ShooterPC;

	bool m_IsStart;

	int32 m_CurrentScore;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Score", meta = (AllowPrivateAccess = true))
	int32 m_WinScore;

	bool m_Clear;

public:
	FORCEINLINE int32 GetCurrentScore() const { return m_CurrentScore; }

	UFUNCTION(BlueprintCallable)
	bool IsClear() const { return m_Clear; }
};
