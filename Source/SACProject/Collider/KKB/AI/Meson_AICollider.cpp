// Fill out your copyright notice in the Description page of Project Settings.


#include "Meson_AICollider.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"

// Sets default values
AMeson_AICollider::AMeson_AICollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetCollisionProfileName("AIAttackOverlap");
}

// Called when the game starts or when spawned
void AMeson_AICollider::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeson_AICollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeson_AICollider::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AMeson_AICollider::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

