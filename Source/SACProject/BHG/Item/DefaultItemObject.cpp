// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultItemObject.h"

// Sets default values
ADefaultItemObject::ADefaultItemObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DefaultItemBox"));
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DefaultItemParticle"));


	SetRootComponent(m_DefaultBox);

	m_Particle->SetupAttachment(m_DefaultBox);

	m_Particle->SetWorldLocation(GetActorLocation());

}

// Called when the game starts or when spawned
void ADefaultItemObject::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void ADefaultItemObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

