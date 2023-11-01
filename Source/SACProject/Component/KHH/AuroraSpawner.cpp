// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraSpawner.h"
#include "../../AI/KHH/AuroraAICharacter.h"

// Sets default values
AAuroraSpawner::AAuroraSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(m_Root);


#if UE_BUILD_DEBUG
	m_Root->bVisualizeComponent = true;
#endif


#if WITH_EDITORONLY_DATA

	m_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	m_Arrow->SetupAttachment(m_Root);

#endif
}

void AAuroraSpawner::AuroraSpawn()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	float HalfHeight = 0.f;

	TObjectPtr<AAuroraAICharacter> DefaultObj = Cast<AAuroraAICharacter>(m_Spawn->GetDefaultObject());

	if (IsValid(DefaultObj))
	{
		HalfHeight = DefaultObj->GetHalfHeight();

		GetWorld()->SpawnActor<AAuroraAICharacter>(m_Spawn, GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight), GetActorRotation(), ActorParam);
	}
}

// Called when the game starts or when spawned
void AAuroraSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuroraSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

