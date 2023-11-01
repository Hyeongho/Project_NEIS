// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../SACProjectGameModeBase.h"
#include "BHG_GameMode.generated.h"


/**
 * 
 */
UCLASS()
class SACPROJECT_API ABHG_GameMode : public ASACProjectGameModeBase
{
	GENERATED_BODY()

public:
	ABHG_GameMode();

protected:
	UPROPERTY(Category = "MainUI", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget>		mMainUIClass;

	TObjectPtr<class UBHGDefaultUserWidget>		mMainWidget;

	UPROPERTY(Category = "SkillUI", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget>		mSkillUIClass;

	TObjectPtr<class UBHGSkillUI>		mSkillUIWidget;

	UPROPERTY(Category = "BossHPUI", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget>		m_BossHPUIClass;

	TObjectPtr<class UBossHpWidget>		m_BossHPUIWidget;


	UPROPERTY(Category = "BGM", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASoundPlayer>	m_BGMPlayerClass;

	TObjectPtr<class ASoundPlayer> m_BGMPlayer;

public:
	class UBossHpWidget* GetBossHpBar() { return m_BossHPUIWidget; }
	

protected:
	UPROPERTY(Category = "BossSpawner", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADefaultSpawnObject>	m_BossSpawnObject;

	UPROPERTY(Category = "BossSpawnOn", EditAnywhere, BlueprintReadWrite)
	bool	BossSpawn;

	UPROPERTY(Category = "Portal", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APortalObject>		m_PortalObject;



	bool	BossEnd;
	float	PortalTime;

	bool UIEnable;
	float UIVisiableTime;

public:
	UFUNCTION(BlueprintCallable)
	const bool& GetBossSpawn() const { return BossSpawn; }

	UFUNCTION(BlueprintCallable)
		void SetBossSpawn(bool SpawnOn) { BossSpawn = SpawnOn; }

public:
	void BossStart();
	void PlayerAttack();
	void PortalStart();

	
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

};
