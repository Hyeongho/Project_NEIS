// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMonsterProjectile.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "../../AI/CJH/ShooterMonster.h"

AShooterMonsterProjectile::AShooterMonsterProjectile()
	: Super()
	, m_InitialTargetLocation(FVector(0.0f))
	, m_LockOn(false)
	, m_LockOnTime(0.7f)
	, m_Damage(10)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::SphereBeginOverlap);
	m_CollisionSphere->OnComponentHit.AddDynamic(this, &ThisClass::SphereHit);

	GetWorldTimerManager().SetTimer(m_LockOnTimer, this, &ThisClass::LockOn, m_LockOnTime);
}

void AShooterMonsterProjectile::RotateToTarget()
{
	if (IsValid(m_Target))
	{
		FVector Dir = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), m_InitialTargetLocation);
		m_ProjectileMovement->Velocity = Dir * m_Speed;
	}
}

void AShooterMonsterProjectile::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어가 맞았을 경우
	AShooterCharacter* Shooter = Cast<AShooterCharacter>(OtherActor);
	if (IsValid(Shooter))
	{
		// Owner는 몬스터로 설정되어 있음
		if (AShooterMonster* Monster = Cast<AShooterMonster>(GetOwner()))
		{
			UGameplayStatics::ApplyDamage(Shooter, m_Damage, Monster->GetController(), Monster, UDamageType::StaticClass());

			Explosion();
		}
	}
}

void AShooterMonsterProjectile::SphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explosion();
}

void AShooterMonsterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (m_LockOn)
	//{
	//	RotateToTarget();
	//}
}

void AShooterMonsterProjectile::LockOn()
{
	m_LockOn = true;

	if (IsValid(m_Target))
	{
		FVector Dir = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), m_InitialTargetLocation);
		m_ProjectileMovement->Velocity = Dir * m_Speed;
		m_ProjectileMovement->ProjectileGravityScale = m_GravityScale * 0.8f;
	}
}

void AShooterMonsterProjectile::BulletHit_Implementation(FHitResult HitResult)
{
	Explosion();
}

void AShooterMonsterProjectile::SetTarget(AActor* InTarget)
{
	m_Target = InTarget;

	m_InitialTargetLocation = m_Target->GetActorLocation();
}
