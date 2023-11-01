// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateProjectile.h"
#include "../Component/AbilityComponent.h"

AUltimateProjectile::AUltimateProjectile()
	: Super()
{
	
	m_Box->SetNotifyRigidBodyCollision(true);
	m_Box->SetGenerateOverlapEvents(true);

	m_MaxDamage = 50;
	m_MinDamage = 10;

	m_Length = 1000.f; 
}

void AUltimateProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Length -= m_ProjectieSpeed * DeltaTime;

	if (m_Length <= 0)
		Destroy();
}

void AUltimateProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (m_MinDamage == m_MaxDamage)
		m_TrueDamage = m_MaxDamage;

	else
		m_TrueDamage = FMath::RandRange(m_MinDamage, m_MaxDamage);
}

void AUltimateProjectile::ProjectileFire(FVector Velocity, ACharacter* Shooter)
{
	Super::ProjectileFire(Velocity, Shooter);
}

void AUltimateProjectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	m_Target = Cast<ACharacter>(OtherActor);

	GetWorld()->SpawnActor<ABaseEffect>(m_ProjectileEffect, Hit.ImpactPoint, GetActorRotation());
	
}

void AUltimateProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	m_Target = Cast<ACharacter>(OtherActor);

	GetWorld()->SpawnActor<ABaseEffect>(m_ProjectileEffect, SweepResult.ImpactPoint, GetActorRotation());

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 

		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedUltimate"), m_Shooter, m_Target, m_TrueDamage);
		}
	}
}
