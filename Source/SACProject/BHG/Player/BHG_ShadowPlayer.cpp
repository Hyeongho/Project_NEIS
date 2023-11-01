// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_ShadowPlayer.h"
#include "../Component/AbilityComponent.h"
#include "../Ability/DefaultAbility.h"
#include "../Ability/DefaultAttackAbility.h"
#include "../Ability/ShurikenAttackAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "BHG_PlayerController.h"
#include "BHG_Player.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Animation/BHG_PlayerShadowAnimInstance.h"
#include "../Effect/BaseEffect.h"


ABHG_ShadowPlayer::ABHG_ShadowPlayer()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/BHG/Blueprints/Animation/BA_ShadowAnimation.BA_ShadowAnimation_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));


	//Ability Create
	m_Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability"));
	m_Ability->SetPlayer(true);

}

void ABHG_ShadowPlayer::BeginPlay()
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

	//Ability Setting

	if (IsValid(m_Ability))
	{
		m_Ability->GiveAbility(m_DefaultAttack);
		m_Ability->GiveAbility(m_ShurikenAttack);
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

void ABHG_ShadowPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (IsValid(m_Player))
	{
		SetActorRotation(m_Player->GetActorRotation());	

		FVector PlayerBackLoc = m_Player->GetActorForwardVector() * -1.f;
		PlayerBackLoc *= 40.f;
		
		SetActorLocation(m_Player->GetActorLocation() + PlayerBackLoc);		

		UBHG_PlayerAnimInstance* PlayerAnim = Cast<UBHG_PlayerAnimInstance>(m_Player->GetMesh()->GetAnimInstance());
		UBHG_PlayerShadowAnimInstance* ShadowAnim = Cast<UBHG_PlayerShadowAnimInstance>(GetMesh()->GetAnimInstance());

		ShadowAnim->SetForwardSpeed(PlayerAnim->GetForwardSpeed());
		ShadowAnim->SetRightSpeed(PlayerAnim->GetRightSpeed());
	}
}

void ABHG_ShadowPlayer::SetPlayer(ABHG_Player* Player)
{
	m_Player = Player;
}

void ABHG_ShadowPlayer::DefaultAttackKey()
{
	if (IsValid(m_Ability))
		m_Ability->ActivatedAbility(TEXT("DefaultAttack"));
}

void ABHG_ShadowPlayer::ShurikenAttackkey()
{
	if (IsValid(m_Ability))
		m_Ability->ActivatedAbility(TEXT("ShurikenAttack"));
}


