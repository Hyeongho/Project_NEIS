// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostActor.h"
#include "Components/PoseableMeshComponent.h"

// Sets default values
AGhostActor::AGhostActor()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PoseableComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));

	SetRootComponent(m_PoseableComp);

	OpacityTime = 1.f;

}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();

	//Material Setting
	int32 ElementCount = m_PoseableComp->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* TMaterial = m_PoseableComp->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(TMaterial);
	}
	
}

// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpacityTime -= DeltaTime;

	if (OpacityTime <= 0.f)
		Destroy();

	if (IsValid(this))
	{
		for (auto& Mtrl : mMaterialArray)
		{		
			float Opacity = 0 + OpacityTime;

			Mtrl->SetScalarParameterValue(TEXT("Opacity"), Opacity);
			Mtrl->SetVectorParameterValue(TEXT("Color"), mColor);
		}
	}
}

void AGhostActor::CopyAnimation(USkeletalMeshComponent* CopyComp)
{	
	m_PoseableComp->CopyPoseFromSkeletalComponent(CopyComp);
}

void AGhostActor::SetGhostColor(FVector GhostColor)
{
	mColor = GhostColor;
}

