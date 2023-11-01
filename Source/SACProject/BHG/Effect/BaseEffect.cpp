// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffect.h"

ABaseEffect::ABaseEffect()
	: Super()
{
	m_Offset = FVector(0.0, 0.0, 0.0);
}

void ABaseEffect::SetEffectOwner(ACharacter* EffectOwner)
{
	m_Owner = EffectOwner;
}

void ABaseEffect::SetOffset(FVector Offset)
{
	m_Offset = Offset;
}

void ABaseEffect::BeginPlay()
{
	Super::BeginPlay();
	m_Particle->OnSystemFinished.AddDynamic(this, &ABaseEffect::PariticleFinish);
}

void ABaseEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEffect::DeleteEffect()
{
	Destroy();
}

void ABaseEffect::PariticleFinish(UParticleSystemComponent* System)
{
	Destroy();
}


