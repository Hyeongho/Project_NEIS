// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPointEffect.h"
#include "../Player/BHG_Player.h"

AHealPointEffect::AHealPointEffect() 
	: Super()
{
	m_HealBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HealPointBox"));

	m_HealBox->SetupAttachment(m_Particle);

	m_HealBox->SetBoxExtent(FVector(100.0, 100.0, 100.0));
	m_HealBox->bHiddenInGame = false;

	m_HealBox->SetGenerateOverlapEvents(true);
	m_HealBox->OnComponentBeginOverlap.AddDynamic(this, &AHealPointEffect::HealBoxBeginOverlap);

	m_HealBox->SetNotifyRigidBodyCollision(true);
	m_HealBox->OnComponentHit.AddDynamic(this, &AHealPointEffect::OnComponentHitEvent);

}

void AHealPointEffect::BeginPlay()
{
	Super::BeginPlay();
}

void AHealPointEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealPointEffect::HealBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ABHG_Player* BHGPlayer = Cast<ABHG_Player>(OtherActor);

	if (IsValid(BHGPlayer))
	{
		BHGPlayer->StartHealEffect();
		DeleteEffect();
	}
}

void AHealPointEffect::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABHG_Player* BHGPlayer = Cast<ABHG_Player>(OtherActor);

	if (IsValid(BHGPlayer))
	{
		BHGPlayer->StartHealEffect();
		DeleteEffect();
	}
}

