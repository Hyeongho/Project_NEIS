// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_DoublePainCol.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"

AGrux_DoublePainCol::AGrux_DoublePainCol()
{
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetBoxExtent(FVector(200.f, 400.f, 150.f));

	m_Damage = 100;
}

void AGrux_DoublePainCol::BeginPlay()
{
	Super::BeginPlay();
}

void AGrux_DoublePainCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrux_DoublePainCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AKwang_PlayerCharacter* KwangPlayer = Cast<AKwang_PlayerCharacter>(OtherActor);

	// 데미지 처리
	if (IsValid(KwangPlayer)) {
		KwangPlayer->TakeDamage(m_Damage, FDamageEvent(), nullptr, m_ColOwner);
	}
}

void AGrux_DoublePainCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

