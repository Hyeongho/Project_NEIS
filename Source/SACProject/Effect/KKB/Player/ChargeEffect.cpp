// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeEffect.h"

// Sets default values
AChargeEffect::AChargeEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(m_Body);
}

// Called when the game starts or when spawned
void AChargeEffect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChargeEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChargeEffect::SetEffectLocation(const FVector& Loc)
{
	m_Body->SetWorldLocation(Loc);
}

void AChargeEffect::SetEffectRotation(const FRotator& Rot)
{
	m_Body->SetWorldRotation(Rot);
}
