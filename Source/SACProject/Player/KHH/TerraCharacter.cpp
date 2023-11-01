// Fill out your copyright notice in the Description page of Project Settings.


#include "TerraCharacter.h"
#include "TerraAnimInstance.h"
#include "../DefaultPlayerState.h"
#include "../../UI/KHH/FrozenCaveWidget.h"
#include "../../GameMode/KHH/IceLandGameModeBase.h"

ATerraCharacter::ATerraCharacter()
{
	m_TerraType = ETerraType::Default;

	m_MPRecovery = 0.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTerra/Characters/Heroes/Terra/Meshes/Terra.Terra'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/KHH/Player/AB_Terra.AB_Terra_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	m_SpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	m_SpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	m_SpringArm->TargetArmLength = 500.f;
}

void ATerraCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIceLandGameModeBase* GameMode = Cast<AIceLandGameModeBase>(GetWorld()->GetAuthGameMode());

	m_FrozenCaveWidget = GameMode->GetFrozenCaveWidget();

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (IsValid(DefaultPlayerState))
	{
		m_FrozenCaveWidget->SetPlayerCurHP(DefaultPlayerState->GetHPMax());
		m_FrozenCaveWidget->SetPlayerMaxHP(DefaultPlayerState->GetHPMax());

		m_FrozenCaveWidget->SetPlayerCurMP(DefaultPlayerState->GetMPMax());
		m_FrozenCaveWidget->SetPlayerMaxMP(DefaultPlayerState->GetMPMax());
	}
}

void ATerraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ADefaultPlayerState* DefaultPlayerState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (IsValid(DefaultPlayerState))
	{
		float MPRecoveryPerSecond = 1.0f;
		m_MPRecovery += MPRecoveryPerSecond * DeltaTime;

		if (m_MPRecovery >= 1.0f)
		{
			DefaultPlayerState->AddMP(1);
			m_MPRecovery = 0.f;
		}

		m_FrozenCaveWidget->SetPlayerCurHP(DefaultPlayerState->GetHP());
		m_FrozenCaveWidget->SetPlayerCurMP(DefaultPlayerState->GetMP());
	}
}

void ATerraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATerraCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void ATerraCharacter::Attack()
{
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;

	FVector End = Start + GetActorForwardVector() * 200.f;

	FHitResult result;

	FCollisionQueryParams param(NAME_None, false, this);

	bool Collision = GetWorld()->SweepSingleByChannel(result, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel5, FCollisionShape::MakeSphere(100.f), param);

#if ENABLE_DRAW_DEBUG

	//FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	//DrawDebugSphere(GetWorld(), (Start + End) / 2.f, 100, 20, DrawColor, false, 20.f);

#endif

	if (Collision)
	{
		FActorSpawnParameters ActorParam;
		ActorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FHitResult LineResult;

		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(10.f, DmgEvent, GetController(), this);

	}

	else
	{

	}
}
