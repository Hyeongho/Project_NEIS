// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnObject.h"
#include "../AI/AI_Monster.h"
#include "../GameMode/BHG_GameMode.h"

AMonsterSpawnObject::AMonsterSpawnObject()
	:Super()
{
	m_Start = false;
}

void AMonsterSpawnObject::MonsterDie()
{
	m_LiveMonster--;

	if (m_LiveMonster == 0)
	{
		ABHG_GameMode* BHG_Mode = Cast<ABHG_GameMode>(GetWorld()->GetAuthGameMode());

		BHG_Mode->BossStart();
	}

}

void AMonsterSpawnObject::BeginPlay()
{
	Super::BeginPlay();

	m_Time = 0.f;
	m_LiveMonster = m_MonsterCount;

}

void AMonsterSpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_Start)
	{
		m_StartTime += DeltaTime;

		if (m_StartTime > 3.5f)
		{
			m_Start = true;
			m_StartTime = 0.f;
		}
	}

	if (m_Start)
	{

		int Count = m_Monsters.Num();

		//몬스터의 개수가 1개이상, 몬스터의 맥스카운트가 0이 아닐경우 소환한다. 

		if (Count > 0 && m_MonsterCount > 0)
		{
			m_Time += DeltaTime;

			if (m_Time >= m_RespawnTime)
			{
				int32 RandomNumber = FMath::RandRange(0, Count - 1);

				float RandomXValue = FMath::RandRange(-1000.f, 1000.f);
				float RandomYValue = FMath::RandRange(-1000.f, 1000.f);

				FVector OriginLoc = GetActorLocation();
				OriginLoc.X += RandomXValue;
				OriginLoc.Y += RandomYValue;

				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				AAI_Monster* AIMonster = GetWorld()->SpawnActor<AAI_Monster>(m_Monsters[RandomNumber], OriginLoc,
					FRotator::ZeroRotator, ActorParam);

				AIMonster->SetSpawner(this);

				AIMonster->GetCharacterMovement()->GravityScale = 10.f;


				m_MonsterCount--;

				m_Time = 0.f;

			}
		}
	}

}
