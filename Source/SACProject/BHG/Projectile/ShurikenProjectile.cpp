// Fill out your copyright notice in the Description page of Project Settings.


#include "ShurikenProjectile.h"
#include "../Component/AbilityComponent.h"

AShurikenProjectile::AShurikenProjectile()
	: Super()
{
	m_Box->SetNotifyRigidBodyCollision(false);
	m_Box->SetGenerateOverlapEvents(true);

	m_MaxDamage = 50;
	m_MinDamage = 10;
}

void AShurikenProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_Length = 2000.f;

	if (m_MinDamage == m_MaxDamage)
		m_TrueDamage = m_MaxDamage;

	else
		m_TrueDamage = FMath::RandRange(m_MinDamage, m_MaxDamage);
}

void AShurikenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(IsValid(this))
	m_Mesh->AddWorldRotation(FRotator(0.0, 1080.f * DeltaTime, 0.0));


	if (IsValid(this))
	{
		m_Length -= m_ProjectieSpeed * DeltaTime;

		if (m_Length <= 0.f)
			Destroy();
	}

}

void AShurikenProjectile::ProjectileFire(FVector Velocity, ACharacter* Shooter)
{
	Super::ProjectileFire(Velocity, Shooter);
}

void AShurikenProjectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AShurikenProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	m_Target = Cast<ACharacter>(OtherActor);

	FVector HitLoc = SweepResult.ImpactPoint;
	HitLoc.Z -= 75.f;

	GetWorld()->SpawnActor<ABaseEffect>(m_ProjectileEffect, HitLoc, GetActorRotation());

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 

		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedShuriken"), m_Shooter, m_Target, m_TrueDamage);
		}
	}
}
