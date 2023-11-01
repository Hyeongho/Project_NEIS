// Fill out your copyright notice in the Description page of Project Settings.


#include "FireLandGameMode.h"
#include "../../Player/DefaultPlayerState.h"
#include "../../Player/KKB/Kwang_PlayerCharacter.h"
#include "../../Player/KKB/Kwang_Controller.h"
#include "../../UI/KKB/FireLandWidget.h"
#include "../../UI/KKB/Kwang_UserWidget.h"

AFireLandGameMode::AFireLandGameMode()
{
	DefaultPawnClass = AKwang_PlayerCharacter::StaticClass();
	PlayerControllerClass = AKwang_Controller::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();

	// Widget class Set
	static ConstructorHelpers::FClassFinder<UUserWidget> FireLandWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KKB/UI/FireLandWidget.FireLandWidget_C'"));

	if (FireLandWidgetClass.Succeeded()) 
		m_FireLandWidgetClass = FireLandWidgetClass.Class;

	// Widget class Set
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KKB/UI/KwangUI.KwangUI_C'"));

	if (PlayerWidgetClass.Succeeded())
		m_PlayerWidgetClass = PlayerWidgetClass.Class;



	// Auido Set
	m_Phase1Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Phase1Audio"));
	m_Phase1Audio->SetupAttachment(RootComponent);
	m_Phase1Audio->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset1(TEXT("/Script/Engine.SoundWave'/Game/KKB/Sound/Phase1.Phase1'"));

	if(SoundAsset1.Succeeded())
		m_Phase1Audio->SetSound(SoundAsset1.Object);


	m_Phase2Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Phase2Audio"));
	m_Phase2Audio->SetupAttachment(RootComponent);
	m_Phase2Audio->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset2(TEXT("/Script/Engine.SoundWave'/Game/KKB/Sound/Phase2.Phase2'"));

	if (SoundAsset2.Succeeded())
		m_Phase2Audio->SetSound(SoundAsset2.Object);
}

void AFireLandGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AFireLandGameMode::InitGameState()
{
	Super::InitGameState();
}

void AFireLandGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AFireLandGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_FireLandWidgetClass))
	{
		m_FireLandWidget = CreateWidget<UFireLandWidget>(GetWorld(), m_FireLandWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("FireLand m_FireLandWidget Set!"));

		if (IsValid(m_FireLandWidget)) {
			m_FireLandWidget->AddToViewport();
			m_FireLandWidget->SetVisibility(ESlateVisibility::Hidden);

			UE_LOG(LogTemp, Warning, TEXT("FireLand BossWidget Maked!"));
		}
	}

	if (IsValid(m_PlayerWidgetClass))
	{
		m_PlayerWidget = CreateWidget<UKwang_UserWidget>(GetWorld(), m_PlayerWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("FireLand m_PlayerWidget Set!"));

		if (IsValid(m_PlayerWidget)) {
			m_PlayerWidget->AddToViewport();
			m_PlayerWidget->SetVisibility(ESlateVisibility::Hidden);

			UE_LOG(LogTemp, Warning, TEXT("FireLand PlayerWidget Maked!"));
		}
	}


	UGameplayStatics::GetPlayerController(this, 0)->GetPlayerState<ADefaultPlayerState>()->InitPlayerData(FName("Kwang"));
}

void AFireLandGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireLandGameMode::Audio_Phase1Start()
{
	if (IsValid(m_Phase1Audio))
		m_Phase1Audio->Play();
}

void AFireLandGameMode::Audio_Phase2Start()
{
	if (IsValid(m_Phase2Audio))
		m_Phase2Audio->Play();
}

void AFireLandGameMode::Audio_Phase1Stop()
{
	if (IsValid(m_Phase1Audio))
		m_Phase1Audio->Stop();
}

void AFireLandGameMode::Audio_Phase2Stop()
{
	if (IsValid(m_Phase2Audio))
		m_Phase2Audio->Play();
}
