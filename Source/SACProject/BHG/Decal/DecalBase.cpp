// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalBase.h"

ADecalBase::ADecalBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADecalBase::SetDecalOwner(AActor* DecalOwner)
{
	m_DecalOwner = DecalOwner;
}

void ADecalBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADecalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
