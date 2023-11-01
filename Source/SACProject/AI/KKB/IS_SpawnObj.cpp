// Fill out your copyright notice in the Description page of Project Settings.


#include "IS_SpawnObj.h"
#include "IS_AICharacter.h"
#include "../../Component/KKB/CoolDownComponent.h"

AIS_SpawnObj::AIS_SpawnObj() :
	m_NormalSpawnCount(0),
	m_ISSpawnTime(3.f),
	m_ISSpawnRangeTime(1.f),
	m_ISSpawnIsRand(true),
	m_ISSpawnMaxCount(3),
	m_IsSpawnStart(false),
	m_SpawnWaitTime(0.f),
	m_SpawnWaitMaxTime(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Body
	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyComponent"));
	SetRootComponent(m_Body);
	m_Body->SetBoxExtent(FVector(150.0, 150.0, 150.0));
	m_Body->SetCollisionProfileName("OverlapAll");

	// Cooldown Comp
	m_MonsterRespawnCooldown = CreateDefaultSubobject<UCoolDownComponent>(TEXT("RespawnCooldown"));
	m_MonsterRespawnCooldown->SetCooldownTime(m_ISSpawnTime);


	// RespawnEffect Setting
	m_RespawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RespawnEffect"));
	m_RespawnEffect->SetupAttachment(RootComponent);
	m_RespawnEffect->SetAutoActivate(false);
	m_RespawnEffect->OnSystemFinished.AddDynamic(this, &AIS_SpawnObj::OnParticleSystemFinished);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Forging/P_ForgeFinishGlow.P_ForgeFinishGlow'"));

	if (ParticleAsset.Succeeded()) 
		m_RespawnEffect->SetTemplate(ParticleAsset.Object);



	// wait Time Randomize
	float RandTime = FMath::FRandRange(0.5f, 2.0f);

	m_SpawnWaitMaxTime = RandTime;
}

// Called when the game starts or when spawned
void AIS_SpawnObj::BeginPlay()
{
	Super::BeginPlay();
}

void AIS_SpawnObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsSpawnStart) {
		m_SpawnWaitTime += DeltaTime;

		if (m_SpawnWaitTime < m_SpawnWaitMaxTime)
			return;


		if (IsValid(m_MonsterRespawnCooldown)) {
			if (m_MonsterRespawnCooldown->IsCooldown())
				m_MonsterRespawnCooldown->UpdateCooldown(DeltaTime);
			else
				PlayEffect();
		}
	}

}

void AIS_SpawnObj::SpawnMonster(bool IsElite)
{
	GetWorld()->SpawnActor<AIS_AICharacter>(GetActorLocation(), GetActorRotation());

	if (m_ISSpawnIsRand) {
		float RandCooltime = FMath::FRandRange(0.f, m_ISSpawnRangeTime);
		RandCooltime -= m_ISSpawnRangeTime / 2.f;
		RandCooltime += m_ISSpawnTime;

		m_MonsterRespawnCooldown->SetCooldownTime(RandCooltime);
	}

	m_MonsterRespawnCooldown->StartCooldown();

	m_NormalSpawnCount++;

	if (m_NormalSpawnCount >= m_ISSpawnMaxCount) 
		Destroy();
}

void AIS_SpawnObj::PlayEffect()
{
	if (IsValid(m_RespawnEffect)) 
		m_RespawnEffect->Activate();

	SpawnMonster();
}

void AIS_SpawnObj::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	if (IsValid(m_RespawnEffect)) 
		m_RespawnEffect->Deactivate();
}
