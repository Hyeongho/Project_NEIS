// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_UltimateShadow.h"
#include "../Effect/BaseEffect.h"
#include "../SpawnObject/ShadowSpawnObject.h"

ABHG_UltimateShadow::ABHG_UltimateShadow()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/BHG/Blueprints/Animation/BA_UltimateShadowAnimation.BA_UltimateShadowAnimation_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));


}

void ABHG_UltimateShadow::SetOwnerActor(AActor* OwnerActor)
{
	mOwnerActor = OwnerActor;
}

void ABHG_UltimateShadow::SetDestorySpawner()
{
	Cast<AShadowSpawnObject>(mOwnerActor)->SpawnerDestory();
}

void ABHG_UltimateShadow::SetDestoryEffect()
{
	Cast<AShadowSpawnObject>(mOwnerActor)->SpawnerEffect();
}

void ABHG_UltimateShadow::BeginPlay()
{
	Super::BeginPlay();

	//Material Setting
	int32 ElementCount = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* TMaterial = GetMesh()->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(TMaterial);
	}

	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetVectorParameterValue(TEXT("ShadowColor"), FVector(0.0, 0.0, 0.0));
		Mtrl->SetScalarParameterValue(TEXT("ShadowOpacity"), 0.1f);
	}
	
	//Effect Setting
	if (IsValid(m_ShadowEffect))
	{
		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ABaseEffect* ShadowEffect = GetWorld()->SpawnActor<ABaseEffect>(m_ShadowEffect, GetActorLocation(),
			FRotator::ZeroRotator, ActorParam);
		ShadowEffect->SetEffectOwner(this);
	}


}

void ABHG_UltimateShadow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(mOwnerActor))
	{
		FRotator NewRotation = (mOwnerActor->GetActorLocation() - GetActorLocation()).Rotation();
		SetActorRotation(NewRotation);
	}
}
