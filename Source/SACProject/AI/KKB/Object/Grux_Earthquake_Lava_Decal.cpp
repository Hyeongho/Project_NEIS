// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux_Earthquake_Lava_Decal.h"
#include "Grux_Earthquake_Lava.h"

// Sets default values
AGrux_Earthquake_Lava_Decal::AGrux_Earthquake_Lava_Decal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_MinScale = 0.0f;
	m_MaxScale = 0.7f;

	GetDecal()->SetWorldScale3D(FVector(m_MinScale, m_MinScale, m_MinScale));

	m_ScaleSpeed = 0.01f;


	UMaterial* DecalMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/BHG/Blueprints/Materials/M_Decal.M_Decal'"));

	if (IsValid(DecalMaterial))
		this->SetDecalMaterial(DecalMaterial);
}

// Called when the game starts or when spawned
void AGrux_Earthquake_Lava_Decal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrux_Earthquake_Lava_Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentScale = GetDecal()->GetRelativeScale3D().Z;

	if (CurrentScale < m_MaxScale) {
		FVector DecalScale = GetDecal()->GetRelativeScale3D();

		DecalScale.X += m_ScaleSpeed;
		DecalScale.Y += m_ScaleSpeed;
		DecalScale.Z += m_ScaleSpeed;

		GetDecal()->SetWorldScale3D(DecalScale);
	}
	else {
		if (IsValid(m_DecalOwner)) 
			Cast<AGrux_Earthquake_Lava>(m_DecalOwner)->DecalEnd();

		Destroy();
	}
}

