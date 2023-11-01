// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	SetRootComponent(m_Body);

#if UE_BUILD_DEBUG
	m_Body->bVisualizeComponent = true;
#endif

	m_Body->SetBoxExtent(FVector(100.0, 100.0, 100.0));

	m_Body->SetCollisionProfileName(TEXT("AISpawnTrigger"));

	m_Body->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	m_Body->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OverlapBegin);

	//m_LevelSequenceClass = LoadObject<UClass>(nullptr, TEXT("/Script/LevelSequence.LevelSequence'/Game/KHH/LevelSequence/TestLevelSequence.TestLevelSequence_C'"));
}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	m_LevelSequence = GetWorld()->SpawnActor<ALevelSequenceActor>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (IsValid(m_LevelSequence))
	{
		m_LevelSequence->SetSequence(LoadObject<ULevelSequence>(nullptr, TEXT("/Script/LevelSequence.LevelSequence'/Game/KHH/LevelSequence/TestLevelSequence.TestLevelSequence'")));
	}
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/*if (IsValid(m_LevelSequence))
	{
		m_LevelSequence->SequencePlayer->Play();
	}*/
}

void ATriggerActor::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

