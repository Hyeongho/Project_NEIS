// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "IceLandGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AIceLandGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AIceLandGameModeBase();

public:
	UPROPERTY(Category = Sound, EditAnywhere, BlueprintReadOnly)
	USoundBase* m_Sound;

private:
	TSubclassOf<UUserWidget> m_FrozenCaveWidgetClass;
	TObjectPtr<class UFrozenCaveWidget> m_FrozenCaveWidget;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool m_IsFadeOut;

public:
	TObjectPtr<class UFrozenCaveWidget> GetFrozenCaveWidget()
	{
		return m_FrozenCaveWidget;
	}

public:
	UFUNCTION()
	void SetFadeOut(bool FadeOut)
	{
		m_IsFadeOut = FadeOut;
	}

	UFUNCTION()
	bool GetFadeOut() const
	{
		return m_IsFadeOut;
	}

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
