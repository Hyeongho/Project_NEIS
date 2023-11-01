// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRockProjectile.h"
#include "../Effect/BaseEffect.h"
#include "../Component/AbilityComponent.h"

ABossRockProjectile::ABossRockProjectile() :
	Super()
{
	m_Box->SetGenerateOverlapEvents(true);


	m_Static = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileStatic");

	m_MeteoEffect = CreateDefaultSubobject<UParticleSystemComponent>("Particle");

	m_Static->SetupAttachment(m_Box);
	m_MeteoEffect->SetupAttachment(m_Static);

}

void ABossRockProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABossRockProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsValid(m_MeteoEffect))
	m_MeteoEffect->SetWorldLocation(GetActorLocation());
}

void ABossRockProjectile::ProjectileFire(FVector Velocity, ACharacter* Shooter)
{
	Super::ProjectileFire(Velocity, Shooter);
}

void ABossRockProjectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	GetWorld()->SpawnActor<ABaseEffect>(m_ProjectileEffect, Hit.ImpactPoint, GetActorRotation());

	m_Target = Cast<ACharacter>(OtherActor);

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 

		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedBossSkill1"), m_Shooter, m_Target, m_TrueDamage);
		}
	}


	Destroy();
}

void ABossRockProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
