// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawnObject.h"
#include "../AI/AI_BossMonster.h"

ABossSpawnObject::ABossSpawnObject() 
	: Super()
{
}

void ABossSpawnObject::BeginPlay()
{
	Super::BeginPlay();

	AAI_BossMonster* AIBossMonster = GetWorld()->SpawnActor<AAI_BossMonster>(m_BossMonster, GetActorLocation(), FRotator(0.0,180.0,0.0));
	AIBossMonster->GetCharacterMovement()->GravityScale = 10.f;

}

void ABossSpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
