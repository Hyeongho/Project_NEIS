// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRockSpawnObject.h"
#include "BossSkill1Object.h"

ABossRockSpawnObject::ABossRockSpawnObject()
	: Super()
{
}

void ABossRockSpawnObject::BeginPlay()
{
	Super::BeginPlay();

	CurruntTime = 0.f;
}

void ABossRockSpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnCount > 0)
	{

		CurruntTime += DeltaTime;

		if (CurruntTime > RespawnTime)
		{

			float RandomXValue = FMath::RandRange(-1500.f, 1500.f);
			float RandomYValue = FMath::RandRange(-1500.f, 1500.f);

			FVector OriginLoc = GetActorLocation();
			OriginLoc.X += RandomXValue;
			OriginLoc.Y += RandomYValue;

			if (IsValid(m_RockObject))
			{
				GetWorld()->SpawnActor<ABossSkill1Object>(m_RockObject, OriginLoc, GetActorRotation());
			}

			CurruntTime = 0.f;

			SpawnCount--;

			if (SpawnCount == 0)
			{
				Destroy();
			}

		}

	
	}

	
	
}
