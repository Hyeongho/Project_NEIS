// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerArrowDecal.h"

APlayerArrowDecal::APlayerArrowDecal() : 
	Super()
{
}

void APlayerArrowDecal::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerArrowDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(m_DecalOwner))
	{
		FVector OwnerFwdVec = m_DecalOwner->GetActorForwardVector();
		OwnerFwdVec *= 80.f;

		SetActorLocation(m_DecalOwner->GetActorLocation() + OwnerFwdVec + FVector(0.0, 0.0, -100.0));
		SetActorRotation(m_DecalOwner->GetActorRotation() + FRotator(-90.0, 0.0, 180.0));
	}
}
