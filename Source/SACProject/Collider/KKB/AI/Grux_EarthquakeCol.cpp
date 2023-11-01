// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_EarthquakeCol.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"

AGrux_EarthquakeCol::AGrux_EarthquakeCol()
{
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	m_Damage = 50;
}

void AGrux_EarthquakeCol::BeginPlay()
{
	Super::BeginPlay();
}

void AGrux_EarthquakeCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrux_EarthquakeCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AKwang_PlayerCharacter* KwangPlayer = Cast<AKwang_PlayerCharacter>(OtherActor);

	// 데미지 처리
	if (IsValid(KwangPlayer)) {
		KwangPlayer->TakeDamage(m_Damage, FDamageEvent(), nullptr, m_ColOwner);
	}
}

void AGrux_EarthquakeCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
