// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMonsterSpawner.h"
#include "Components/BoxComponent.h"
#include "ShooterMonster.h"

// Sets default values
AShooterMonsterSpawner::AShooterMonsterSpawner()
	: Super()
	, m_SpawnCount(3)
	, m_SpawnTime(0.8f)
	, m_CurrentSpawnCount(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxBound = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxBound"));
	m_BoxBound->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(m_BoxBound);

	m_SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	m_SpawnerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_SpawnerMesh->SetupAttachment(GetRootComponent());


	m_TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailComponent"));
	m_TrailComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AShooterMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_TrailParticle))
		m_TrailComponent->SetTemplate(m_TrailParticle);

	//StartSpawn();
}

// Called every frame
void AShooterMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterMonsterSpawner::StartSpawn()
{
	SpawnMonster();
	++m_CurrentSpawnCount;

	GetWorldTimerManager().SetTimer(m_SpawnTimer, this, &ThisClass::ResetSpawn, m_SpawnTime);
}

void AShooterMonsterSpawner::ResetSpawn()
{
	// 스폰 종료
	if (m_CurrentSpawnCount >= m_SpawnCount)
	{
		m_CurrentSpawnCount = 0;
		return;
	}

	StartSpawn();
}

void AShooterMonsterSpawner::SpawnMonster()
{
	const int32 MonsterCount = m_MonsterList.Num();
	if (MonsterCount == 0)
		return;

	int32 SelectedIndex = FMath::RandRange(1, MonsterCount) - 1;

	FVector BoundingBoxSize = m_BoxBound->GetScaledBoxExtent();
	BoundingBoxSize.Z = 0.0f;

	FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), BoundingBoxSize / 2.0f);
	FRotator RandomRotation = FRotator(0.0, FMath::FRandRange(-180.0, 180.0), 0.0);

	GetWorld()->SpawnActor<AShooterMonster>(m_MonsterList[SelectedIndex], RandomLocation, RandomRotation);

	if (IsValid(m_SpawnSound))
		UGameplayStatics::PlaySoundAtLocation(this, m_SpawnSound, RandomLocation);

	if (IsValid(m_SpawnParticle))
	{
		FTransform SpawnTransform = FTransform(RandomRotation, RandomLocation, FVector(1.0f));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_SpawnParticle, SpawnTransform);
	}
}

