// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../../Collider/CJH/ShooterColliderBase.h"

// Sets default values
AShooterProjectileBase::AShooterProjectileBase()
	: Super()
	, m_Speed(1500.0f)
	, m_GravityScale(1.5f)
	, m_BounceCount(0)
	, m_ExplosionTime(3.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	m_CollisionSphere->SetCollisionProfileName(TEXT("PlayerProjectile"));
	SetRootComponent(m_CollisionSphere);

	m_ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	m_ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_ProjectileMesh->SetupAttachment(m_CollisionSphere);


	m_TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailComponent"));
	m_TrailComponent->SetupAttachment(m_ProjectileMesh);

	m_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	m_ProjectileMovement->InitialSpeed = m_Speed;
	m_ProjectileMovement->MaxSpeed = m_Speed;
	m_ProjectileMovement->ProjectileGravityScale = m_GravityScale;
	m_ProjectileMovement->bShouldBounce = true;
	m_ProjectileMovement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AShooterProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	m_CollisionSphere->OnComponentHit.AddDynamic(this, &ThisClass::OnSphereHit);

	if (IsValid(m_TrailParticle))
		m_TrailComponent->SetTemplate(m_TrailParticle);

	m_ProjectileMovement->InitialSpeed = m_Speed;
	m_ProjectileMovement->MaxSpeed = m_Speed;
	m_ProjectileMovement->ProjectileGravityScale = m_GravityScale;

	GetWorldTimerManager().SetTimer(m_ExplosionTimer, this, &ThisClass::Explosion, m_ExplosionTime);
}

void AShooterProjectileBase::Explosion()
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

void AShooterProjectileBase::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	++m_BounceCount;

	if (m_BounceCount <= m_BounceCountMax)
	{
		m_ProjectileMovement->MaxSpeed = m_Speed / 3.0f;
		if (IsValid(m_BounceSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, m_BounceSound, GetActorLocation());
		}
	}
}

// Called every frame
void AShooterProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

