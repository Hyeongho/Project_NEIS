// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_BaseAttackCol.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"

AGrux_BaseAttackCol::AGrux_BaseAttackCol()
{
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetBoxExtent(FVector(200.f, 200.f, 200.f));

	m_Damage = 50;
}

void AGrux_BaseAttackCol::BeginPlay()
{
	Super::BeginPlay();
}

void AGrux_BaseAttackCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrux_BaseAttackCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AKwang_PlayerCharacter* KwangPlayer = Cast<AKwang_PlayerCharacter>(OtherActor);

	// 데미지 처리
	if (IsValid(KwangPlayer)) {
		KwangPlayer->TakeDamage(m_Damage, FDamageEvent(), nullptr, m_ColOwner);
	}
}

void AGrux_BaseAttackCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
