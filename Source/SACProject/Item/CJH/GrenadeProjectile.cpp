// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../../Collider/CJH/ShooterColliderBase.h"

// Sets default values
AGrenadeProjectile::AGrenadeProjectile()
	: Super()
	, m_ExplosionTime(3.0f)
	, m_BounceCount(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	m_CollisionSphere->SetCollisionProfileName(TEXT("PlayerProjectile"));
	SetRootComponent(m_CollisionSphere);

	m_GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrenadeMesh"));
	m_GrenadeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_GrenadeMesh->SetupAttachment(m_CollisionSphere);


	m_SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrail"));
	m_SmokeTrail->SetupAttachment(m_GrenadeMesh);

	m_GrenadeMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("GrenadeMovement"));
	m_GrenadeMovement->InitialSpeed = 2000.0f;
	m_GrenadeMovement->MaxSpeed = 1500.0f;
	m_GrenadeMovement->ProjectileGravityScale = 1.5f;
	m_GrenadeMovement->bShouldBounce = true;
	m_GrenadeMovement->bRotationFollowsVelocity = true;

}

// Called when the game starts or when spawned
void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	m_CollisionSphere->OnComponentHit.AddDynamic(this, &AGrenadeProjectile::OnSphereHit);

	if (IsValid(m_SmokeTrailParticle))
		m_SmokeTrail->SetTemplate(m_SmokeTrailParticle);
	
	Shot();
}

void AGrenadeProjectile::Shot()
{

	GetWorldTimerManager().SetTimer(m_ExplosionTimer, this, &AGrenadeProjectile::FinishShot, m_ExplosionTime);
}

void AGrenadeProjectile::FinishShot()
{

	// 이펙트 스폰
	if (IsValid(m_ExplosionParticle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ExplosionParticle, GetActorLocation());
	}
	if (IsValid(m_ExplosionSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_ExplosionSound, GetActorLocation());
	}

	// 데미지처리를 위한 충돌체 스폰
	if (IsValid(m_HitBoxClass))
	{
		const FVector FwdDir = GetActorForwardVector();
		FActorSpawnParameters Params;
		Params.Owner = this;

		GetWorld()->SpawnActor<AShooterColliderBase>(m_HitBoxClass, GetActorLocation(), GetActorRotation(), Params);
	}

	// 제거
	Destroy();
}

void AGrenadeProjectile::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	++m_BounceCount;

	if (m_BounceCount <= m_BounceCountMax)
	{
		m_GrenadeMovement->MaxSpeed = 500.0f;
		if (IsValid(m_BounceSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, m_BounceSound, GetActorLocation());
		}
	}
}

// Called every frame
void AGrenadeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

