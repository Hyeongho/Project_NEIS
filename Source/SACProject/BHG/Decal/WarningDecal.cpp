// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningDecal.h"
#include "Components/DecalComponent.h"
#include "../SpawnObject/BossSkill1Object.h"

AWarningDecal::AWarningDecal() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;

	ScaleTime = 0.3f;

	AddTime = 0.5f;

	ScaleSpeed = 0.05f;
}

void AWarningDecal::BeginPlay()
{
	Super::BeginPlay();

	GetDecal()->SetWorldScale3D(FVector(MinScale, MinScale, MinScale));

	SetDecalOwner(GetOwner());
}

void AWarningDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddTime += DeltaTime;

	float CurrentScale = GetDecal()->GetRelativeScale3D().Y;

	if (CurrentScale < MaxScale)
	{

		if (AddTime > ScaleTime)
		{
			FVector DecalScale = GetDecal()->GetRelativeScale3D();

			DecalScale.X += ScaleSpeed;
			DecalScale.Y += ScaleSpeed;
			DecalScale.Z += ScaleSpeed;

			GetDecal()->SetWorldScale3D(DecalScale);
		}

	}

	else
	{
		MaxOn = true;

		if (IsValid(m_DecalOwner))
		{
			Cast<ABossSkill1Object>(m_DecalOwner)->DecalEnd();
		}

		Destroy();
	}

	
}
