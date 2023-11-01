// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundPlayer.h"

// Sets default values
ASoundPlayer::ASoundPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMcomp"));

	SetRootComponent(m_AudioComp);

	m_AudioComp->OnAudioFinished.AddDynamic(this, &ASoundPlayer::SoundReplay);

}

// Called when the game starts or when spawned
void ASoundPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundPlayer::SoundReplay()
{
	m_AudioComp->Play();
}

void ASoundPlayer::ChangeSound()
{
	if (IsValid(m_Sound))
	{
		
		m_AudioComp->SetSound(m_Sound);
		m_AudioComp->SetPaused(false);
		m_AudioComp->Play();
	}

}

void ASoundPlayer::PauseSound()
{
	m_AudioComp->SetPaused(true);
}

