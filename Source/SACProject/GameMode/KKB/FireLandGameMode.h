// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "FireLandGameMode.generated.h"

class UFireLandWidget;
class UKwang_UserWidget;

/**
 * 
 */
UCLASS()
class SACPROJECT_API AFireLandGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFireLandGameMode();

protected:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent>	 m_Phase1Audio;

	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent>	 m_Phase2Audio;

private:
	TSubclassOf<UUserWidget> m_FireLandWidgetClass;
	TObjectPtr<UFireLandWidget> m_FireLandWidget;

	TSubclassOf<UUserWidget> m_PlayerWidgetClass;
	TObjectPtr<UKwang_UserWidget> m_PlayerWidget;

public:
	inline TObjectPtr<UFireLandWidget> GetFirelandBossWidget() const { return m_FireLandWidget; }
	inline TObjectPtr<UKwang_UserWidget> GetFirelandPlayerWidget() const { return m_PlayerWidget; }

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

public:
	UFUNCTION(BlueprintCallable)
	void Audio_Phase1Start();

	UFUNCTION(BlueprintCallable)
	void Audio_Phase2Start();

	UFUNCTION(BlueprintCallable)
	void Audio_Phase1Stop();
	
	UFUNCTION(BlueprintCallable)
	void Audio_Phase2Stop();
};
