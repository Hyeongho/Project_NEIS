// Fill out your copyright notice in the Description page of Project Settings.


#include "BHG_Player.h"
#include "../Component/AbilityComponent.h"
#include "../Ability/DefaultAbility.h"
#include "../Ability/DefaultAttackAbility.h"
#include "../Ability/ShurikenAttackAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "BHG_PlayerController.h"
#include "BHG_ShadowPlayer.h"
#include "../Decal/DecalBase.h"
#include "../Effect/GhostActor.h"
#include "../Animation/BHG_PlayerShadowAnimInstance.h"
#include "../Effect/BaseEffect.h"
#include "../../Player/DefaultPlayerState.h"
#include "../GameMode/BHG_GameMode.h"

ABHG_Player::ABHG_Player()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/BHG/Blueprints/Animation/BA_PlayerAnimaion.BA_PlayerAnimaion_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//Sound
	m_Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	

	// Camera Setting
	m_SpringArm->TargetArmLength = 1200.f;
	m_SpringArm->SetRelativeLocation(FVector(0.0, 0.0, 150.0));
	m_SpringArm->SetRelativeRotation(FRotator(-40.0, 0.0, 0.0));

	m_SpringArm->SetupAttachment(GetCapsuleComponent());


	//Ability Setting
	m_Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability"));
	m_Ability->SetPlayer(true);

	EvadeOn = false;
}

void ABHG_Player::BeginPlay()
{
	Super::BeginPlay();

	m_Audio->SetPaused(true);

	//Ability Give
	if (IsValid(m_Ability))
	{
		m_Ability->GiveAbility(m_DefaultAttack);
		m_Ability->GiveAbility(m_ShurikenAttack);
		m_Ability->GiveAbility(m_Nightmare);
		m_Ability->GiveAbility(m_ShadowPartner);
		m_Ability->GiveAbility(m_Ultimate);
		m_Ability->GiveAbility(m_CounterAttack);
		m_Ability->GiveAbility(m_Evade);
	}

	//Arrow Decal Create
	if (IsValid(m_ArrowDecal))
	{
		ADecalBase* ArrowDecal = GetWorld()->SpawnActor<ADecalBase>(m_ArrowDecal, GetActorLocation(), GetActorRotation());
		ArrowDecal->SetDecalOwner(Cast<AActor>(this));
	}

}

void ABHG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	RecoveryMPTime += DeltaTime;

	if (RecoveryMPTime > 0.1f)
	{
		ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

		if (IsValid(DefaultPlayerState))
		{
			DefaultPlayerState->AddMP(2);
			RecoveryMPTime = 0.f;
		}
			
	}


	if (EvadeOn)
	{
		GhostTime += DeltaTime;

		if (GhostTime >= 0.05)
		{
			GhostTime = 0.f;

			if (IsValid(m_Ghost))
			{
				FVector Loc = GetActorLocation();

				Loc.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

				FRotator Rot = GetActorRotation();

				Rot.Yaw -= 90.f;

				AGhostActor* Actor = GetWorld()->SpawnActor<AGhostActor>(m_Ghost, Loc, Rot);
				Actor->SetGhostColor(FVector(0.1, 0.1, 0.1));
				Actor->CopyAnimation(GetMesh());
			}
		}
	}

	else
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	}

}

void ABHG_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABHG_Player::OnDamaged(int32 Damage, ACharacter* Shooter, ACharacter* Target, bool Counter)
{

	UBHG_PlayerAnimInstance* Anim = Cast<UBHG_PlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(Anim))
	{
		Anim->SetHitEnable(true);

		ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

		if (IsValid(DefaultPlayerState))
		{
			DefaultPlayerState->AddHP(-Damage);

			if (DefaultPlayerState->GetHP() >= 0)
			{

			}
			
		}	

	}

}

void ABHG_Player::SetShadowPlayer(ABHG_ShadowPlayer* ShadowPlayer)
{
	m_ShadowPlayer = ShadowPlayer;

	GetWorld()->GetTimerManager().SetTimer(m_ShadowTimerHandle, this, &ABHG_Player::ShadowOff, 10.f, false);
	
}

void ABHG_Player::StartHealEffect()
{

	FVector DownLoc = GetActorUpVector() * -100.f;

	GetWorld()->SpawnActor<ABaseEffect>(m_HealEffect, GetActorLocation() + DownLoc, GetActorRotation());

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (IsValid(DefaultPlayerState))
		DefaultPlayerState->AddHP(100);


}

void ABHG_Player::PlayAudio()
{
	m_Audio->SetPaused(false);
	m_Audio->Play();
}

void ABHG_Player::ShadowOff()
{
	Cast<UBHG_PlayerShadowAnimInstance>(m_ShadowPlayer->GetMesh()->GetAnimInstance())->SetShadowAnimType(EShadowAnimType::RespawnEnd);

	m_ShadowPlayer = nullptr;
}

void ABHG_Player::MoveAxis(const FInputActionValue& Value)
{

	bool MoveEnable = m_Ability->GetMoveLock();

	if (!MoveEnable)
	{
		FVector2D MoveVec = Value.Get<FVector2D>();

		AddMovementInput(GetActorForwardVector(), MoveVec.Y);

		AddMovementInput(GetActorRightVector(), MoveVec.X);
	}

}


void ABHG_Player::DefaultAttackKey()
{

	if (IsValid(m_Ability))
	{
		m_Ability->ActivatedAbility(TEXT("DefaultAttack"));

		ABHG_GameMode* BHGGameMode = Cast<ABHG_GameMode>(GetWorld()->GetAuthGameMode());

		if (IsValid(BHGGameMode))
			BHGGameMode->PlayerAttack();

		if (IsValid(m_ShadowPlayer))
			m_ShadowPlayer->DefaultAttackKey();
	}
}

void ABHG_Player::ShurikenAttackkey()
{
	if (IsValid(m_Ability))
	{
		m_Ability->ActivatedAbility(TEXT("ShurikenAttack"));

		if (IsValid(m_ShadowPlayer))
			m_ShadowPlayer->ShurikenAttackkey();
	}
}

void ABHG_Player::CounterAttackKey()
{
	if (IsValid(m_Ability))
	m_Ability->ActivatedAbility(TEXT("CounterAttack"));
}

void ABHG_Player::NightmareKey()
{
	if (IsValid(m_Ability))
	m_Ability->ActivatedAbility(TEXT("Nightmare"));
}

void ABHG_Player::ShadowPartnerKey()
{
	if (IsValid(m_Ability))
	m_Ability->ActivatedAbility(TEXT("ShadowPartner"));
}

void ABHG_Player::UltimateKey()
{
	if (IsValid(m_Ability))
	m_Ability->ActivatedAbility(TEXT("Ultimate"));
}

void ABHG_Player::EvadeKey()
{
	if (IsValid(m_Ability))
	m_Ability->ActivatedAbility(TEXT("Evade"));	
}
