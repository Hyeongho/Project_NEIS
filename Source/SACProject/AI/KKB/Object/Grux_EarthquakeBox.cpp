// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_EarthquakeBox.h"
#include "Grux_Earthquake_Lava.h"
#include "../../../Component/KKB/CoolDownComponent.h"

AGrux_EarthquakeBox::AGrux_EarthquakeBox()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SpawnCycleTime = 0.3f;

	m_LavaSpawnCooldown = CreateDefaultSubobject<UCoolDownComponent>("LavaSpawnCooldownComponent");
	m_LavaSpawnCooldown->SetCooldownTime(m_SpawnCycleTime);

	m_BoxXSize = 1500.f;
	m_BoxYSize = 1500.f;

	m_DamageRelay = 0;

	//m_BoxLifeSpan = 20.f;
}

void AGrux_EarthquakeBox::BeginPlay()
{
	Super::BeginPlay();

	// 블루프린트에서 생성 시, 지정한 값이 적용될 수 있도록 BeginPlay에서 세팅
	if(IsValid(m_LavaSpawnCooldown))
		m_LavaSpawnCooldown->SetCooldownTime(m_SpawnCycleTime);

	// 일정 시간 뒤 소멸하도록 설정.
	//SetLifeSpan(m_BoxLifeSpan);
}

void AGrux_EarthquakeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(m_LavaSpawnCooldown)) {
		if (m_LavaSpawnCooldown->IsCooldown()) {
			m_LavaSpawnCooldown->UpdateCooldown(DeltaTime);
		}
		else {
			float XRandSize = FMath::RandRange(m_BoxXSize * -1.f, m_BoxXSize);
			float YRandSize = FMath::RandRange(m_BoxYSize * -1.f, m_BoxYSize);

			FVector Center = GetActorLocation();
			Center.X += XRandSize;
			Center.Y += YRandSize;

			AGrux_Earthquake_Lava* Lava = GetWorld()->SpawnActor<AGrux_Earthquake_Lava>(Center, GetActorRotation());

			if (m_DamageRelay != 0)
				Lava->SetDamage(m_DamageRelay);

			// 용암 생성 후 쿨타임 개시.
			m_LavaSpawnCooldown->StartCooldown();
		}
	}
}

