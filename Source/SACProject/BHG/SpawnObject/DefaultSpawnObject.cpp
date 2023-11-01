// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultSpawnObject.h"

// Sets default values
ADefaultSpawnObject::ADefaultSpawnObject()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DefaultBox"));

	SetRootComponent(m_DefaultBox);

	m_DefaultBox->SetBoxExtent(FVector(150.0, 150.0, 150.0));

	//m_DefaultBox->bHiddenInGame = false;
	

}

// Called when the game starts or when spawned
void ADefaultSpawnObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultSpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

