// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"
#include "../../GameMode/CJH/ShooterGameMode.h"

AScoreItem::AScoreItem()
	: Super()
	, m_MoveWaitTime(1.0f)
	, m_MoveTime(1.2f)
	, m_Move(false)
	, m_InitialLocation(FVector(0.0f))
{
	m_TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailComponent"));
	m_TrailComponent->SetupAttachment(GetRootComponent());
}

void AScoreItem::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_TrailParticle))
		m_TrailComponent->SetTemplate(m_TrailParticle);

	m_MoveWaitTime = FMath::FRandRange(0.5f, 1.0f);

	GetWorldTimerManager().SetTimer(m_MoveWaitTimer, this, &ThisClass::StartMove, m_MoveWaitTime);
}

void AScoreItem::StartMove()
{
	m_CollisionBox->SetSimulatePhysics(false);

	m_InitialLocation = GetActorLocation();

	m_Move = true;
	GetWorldTimerManager().SetTimer(m_MoveTimer, this, &ThisClass::FinishMove, m_MoveTime);
}

void AScoreItem::FinishMove()
{
	m_Move = false;

	AShooterGameMode* ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ShooterGameMode->AddScore();

	Destroy();
}

void AScoreItem::MoveToPlayer()
{
	FVector PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorLocation();
	float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(m_MoveTimer);
	float MovePercent = ElapsedTime / m_MoveTime;

	FVector LerpLocation = UKismetMathLibrary::VLerp(m_InitialLocation, PlayerLocation, MovePercent);
	SetActorLocation(LerpLocation);
}

void AScoreItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Move)
	{
		MoveToPlayer();
	}
}
