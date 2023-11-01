// Fill out your copyright notice in the Description page of Project Settings.


#include "Meson_PlayerBaseCol.h"

// Sets default values
AMeson_PlayerBaseCol::AMeson_PlayerBaseCol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetCollisionProfileName("PlayerAttackOverlap");
}

// Called when the game starts or when spawned
void AMeson_PlayerBaseCol::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(1.f);
}

// Called every frame
void AMeson_PlayerBaseCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeson_PlayerBaseCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AMeson_PlayerBaseCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


