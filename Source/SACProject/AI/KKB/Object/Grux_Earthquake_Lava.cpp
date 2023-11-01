// Fill out your copyright notice in the Description page of Project Settings.

#include "Grux_Earthquake_Lava.h"
#include "Grux_Earthquake_Lava_Decal.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"
#include "../../../Collider/KKB/AI/Grux_EarthquakeCol.h"
#include "Particles/ParticleSystemComponent.h"

AGrux_Earthquake_Lava::AGrux_Earthquake_Lava() :
	m_DamageRelay(0)
{
	PrimaryActorTick.bCanEverTick = true;


	m_Body = CreateDefaultSubobject<UBoxComponent>("Body");

	SetRootComponent(m_Body);

	m_Body->SetBoxExtent(FVector(100.0, 100.0, 100.0));
	m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	m_LavaEffect = CreateDefaultSubobject<UParticleSystemComponent>("LavaEffect");
	m_LavaEffect->SetupAttachment(RootComponent);
	m_LavaEffect->SetAutoActivate(false);
	m_LavaEffect->OnSystemFinished.AddDynamic(this, &AGrux_Earthquake_Lava::OnParticleSystemFinished);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Fire_Burst_Stalag_01.P_RBurst_Fire_Burst_Stalag_01'"));

	if (ParticleAsset.Succeeded())
		m_LavaEffect->SetTemplate(ParticleAsset.Object);
}

void AGrux_Earthquake_Lava::BeginPlay()
{
	Super::BeginPlay();


	AGrux_Earthquake_Lava_Decal* LavaDecal = GetWorld()->SpawnActor<AGrux_Earthquake_Lava_Decal>(GetActorLocation(), GetActorRotation());

	if (IsValid(LavaDecal)) 
		LavaDecal->SetDecalOwner(this);
}

void AGrux_Earthquake_Lava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrux_Earthquake_Lava::DecalEnd()
{
	// 데칼이 마무리되면 라바 이펙트를 실행하고 콜리더를 만들어 피해를 준다.
	m_LavaEffect->Activate();

	AGrux_EarthquakeCol* Collider = GetWorld()->SpawnActor<AGrux_EarthquakeCol>(GetActorLocation(), GetActorRotation());
	Collider->SetLifeSpan(2.5f);

	if (m_DamageRelay != 0)
		Collider->SetDamage(m_DamageRelay);
}

void AGrux_Earthquake_Lava::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	// 이펙트가 마무리되면 디스트로이 처리한다.
	Destroy();
}
