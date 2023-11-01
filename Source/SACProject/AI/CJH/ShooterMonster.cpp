// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMonster.h"
#include "ShooterMonsterController.h"
#include "../AIState.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../UI/CJH/DamageTextWidget.h"
#include "ShooterMonsterController.h"
#include "../../Collider/CJH/ShooterColliderBase.h"
#include "../../Projectile/CJH/ShooterMonsterProjectile.h"
#include "../../Item/CJH/ShooterItem.h"
#include "../../Component/CJH/ItemDropComponent.h"
#include "../../Item/CJH/ScoreItem.h"

AShooterMonster::AShooterMonster()
	: Super()
	, m_HitReactTime(0.6f)
	, m_CanHitReact(true)
	, m_Stunned(false)
	, m_StunChance(0.15f)
	, m_CanAttack(true)
	, m_AttackCoolTime(2.0f)
	, m_DeathTime(3.0f)
	, m_LongRange(false)
	, m_ScorePoint(0)
{
	AIControllerClass = AShooterMonsterController::StaticClass();

	m_ItemDropComponent = CreateDefaultSubobject<UItemDropComponent>(TEXT("ItemDropComponent"));

	m_AttackSectionNames.Add(FName("Attack"));
}

void AShooterMonster::BeginPlay()
{
	Super::BeginPlay();

	m_MonsterController = Cast<AShooterMonsterController>(GetController());
	m_MonsterController->GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackDistance"), GetAIState()->GetAttackDistance());
	m_MonsterController->GetBlackboardComponent()->SetValueAsFloat(TEXT("InteractionDistance"), GetAIState()->GetInteractionDistance());
	m_MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsLongRange"), m_LongRange);

	SetCanAttack(true);
}

void AShooterMonster::PlayHitMontage(FName SectionName, float PlayRate)
{
	if (m_CanHitReact)
	{
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
		if (IsValid(AnimInst) && IsValid(m_HitMontage))
		{
			AnimInst->Montage_Play(m_HitMontage, PlayRate);
			AnimInst->Montage_JumpToSection(SectionName, m_HitMontage);

			m_CanHitReact = false;
			GetWorldTimerManager().SetTimer(m_HitReactTimer, this, &ThisClass::ResetHitReactTimer, m_HitReactTime);
		}
	}
}

void AShooterMonster::ResetHitReactTimer()
{
	m_CanHitReact = true;
}

void AShooterMonster::ResetAttackTimer()
{
	SetCanAttack(true);
}

void AShooterMonster::PlayDeathMontage(float PlayRate)
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInst) && IsValid(m_DeathMontage))
	{
		AnimInst->Montage_Play(m_DeathMontage, PlayRate);
		AnimInst->Montage_JumpToSection(TEXT("Death"), m_DeathMontage);
	}
}

void AShooterMonster::DestroyMonster()
{
	Destroy();
}

void AShooterMonster::DropItem()
{
	if (m_ScorePoint == 0)
		m_ScorePoint = FMath::RandRange(1, 3);

	for (int32 i = 0; i < m_ScorePoint; ++i)
	{
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(50.0f, 50.0f, 10.0f));
		GetWorld()->SpawnActor<AScoreItem>(m_ScoreItem, RandomLocation, GetActorRotation());
	}

	m_ItemDropComponent->DropItem();
}

float AShooterMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 어차피 Character 클래스의 TakeDamage 기능을 사용하지 않을것이면 굳이 Super call을 하지 않고 따로 계산해도 괜찮을듯?
	//float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetAIState()->GetHP() > 0)
	{
		if (GetAIState()->Damage(DamageAmount))
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PlayDeathMontage();
		}
		else
		{
			const float Stunned = FMath::FRandRange(0.0f, 1.0f);
			if (Stunned <= m_StunChance)
			{
				SetStunned(true);
				PlayHitMontage(FName("HitReactFront"));
			}
		}
	}

	return DamageAmount;
}

void AShooterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AShooterMonster::IsAlive() const
{
	return GetAIState()->GetHP() > 0;
}

void AShooterMonster::Die()
{
	GetMesh()->bPauseAnims = true;

	DropItem();

	GetWorldTimerManager().SetTimer(m_DeathTimer, this, &ThisClass::DestroyMonster, m_DeathTime);
}

void AShooterMonster::ShowDamageText(int32 Damage, const FVector& HitLocation)
{
	if (IsValid(m_DamageTextWidgetClass))
	{
		UDamageTextWidget* DamageWidget = CreateWidget<UDamageTextWidget>(GetWorld(), m_DamageTextWidgetClass);
		if (IsValid(DamageWidget))
		{
			DamageWidget->AddToViewport();
			DamageWidget->SetDamageText(Damage, HitLocation);


			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D ScreenPosition;
			PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
			DamageWidget->SetPositionInViewport(ScreenPosition);
		}
	}
}

void AShooterMonster::ResetStun()
{
	SetStunned(false);
}

void AShooterMonster::PlayAttackMontage(FName SectionName, float PlayRate)
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInst))
	{
		AnimInst->Montage_Play(m_AttackMontage, PlayRate);
		AnimInst->Montage_JumpToSection(SectionName, m_AttackMontage);

		SetCanAttack(false);
		GetWorldTimerManager().SetTimer(m_AttackTimer, this, &ThisClass::ResetAttackTimer, m_AttackCoolTime);
	}

}

FName AShooterMonster::GetAttackSectionName() const
{
	FName SectionName;
	const int32 SectionIndex = FMath::RandRange(0, m_AttackSectionNames.Num() - 1);

	SectionName = m_AttackSectionNames[SectionIndex];

	return SectionName;
}

void AShooterMonster::SpawnHitBox()
{
	if (IsValid(m_HitBoxClass))
	{
		const FVector FwdDir = GetActorForwardVector();

		FVector SpawnLocation = GetActorLocation() + FwdDir * (GetAIState()->GetAttackDistance() / 2.0f + 20.0f);
		FActorSpawnParameters Params;
		Params.Owner = this;

		GetWorld()->SpawnActor<AShooterColliderBase>(m_HitBoxClass, SpawnLocation, GetActorRotation(), Params);
	}
}

void AShooterMonster::SpawnProjectile()
{
	if (IsValid(m_ProjectileClass))
	{
		AActor* Target = Cast<AActor>(m_MonsterController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target))
		{
			FVector Dir = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Target->GetActorLocation());

			const FVector FwdDir = GetActorForwardVector();
			FVector SpawnLocation = GetActorLocation() + FwdDir * 30.0f;
			FActorSpawnParameters Params;
			Params.Owner = this;

			AShooterMonsterProjectile* Projectile = GetWorld()->SpawnActor<AShooterMonsterProjectile>(m_ProjectileClass, SpawnLocation, Dir.Rotation(), Params);
			if (IsValid(Projectile))
				Projectile->SetTarget(Target);
		}
	}
}

void AShooterMonster::BulletHit_Implementation(FHitResult HitResult)
{
	if (IsValid(m_ImpactSound))
		UGameplayStatics::PlaySoundAtLocation(this, m_ImpactSound, GetActorLocation());

	if (IsValid(m_ImpactParticle))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ImpactParticle, HitResult.Location);

	//const float Stunned = FMath::FRandRange(0.0f, 1.0f);
	//if (Stunned <= m_StunChance)
	//{
	//	SetStunned(true);
	//	PlayHitMontage(FName("HitReactFront"));
	//}
}

void AShooterMonster::SetStunned(bool Stunned)
{
	m_Stunned = Stunned;

	m_MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("Stunned"), m_Stunned);
}

void AShooterMonster::SetCanAttack(bool CanAttack)
{
	m_CanAttack = CanAttack;

	m_MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), m_CanAttack);
}
