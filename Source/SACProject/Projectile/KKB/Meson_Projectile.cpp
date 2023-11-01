// Fill out your copyright notice in the Description page of Project Settings.


#include "Meson_Projectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMeson_Projectile::AMeson_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	m_DefaultHitSphere->OnComponentHit.AddDynamic(this, &AMeson_Projectile::OnComponentHitEvent);
	m_DefaultHitSphere->OnComponentBeginOverlap.AddDynamic(this, &AMeson_Projectile::ProjectileBeginOverlap);

	SetRootComponent(m_DefaultHitSphere);

	// Movement Setting
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	m_Movement->SetUpdatedComponent(RootComponent);
	m_Movement->InitialSpeed = 1000.f;
	m_Movement->MaxSpeed = 1000.f; // 최대 속도 설정
	m_Movement->bRotationFollowsVelocity = true;
	m_Movement->ProjectileGravityScale = 0.f;
	m_Movement->bShouldBounce = false; // 장애물과 충돌 시 반사 여부
	m_Movement->OnProjectileStop.AddDynamic(this, &AMeson_Projectile::StopProjectile);


	// HitEffect Setting
	m_HitEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitEffectParticle"));
	m_HitEffect->SetupAttachment(RootComponent);
	m_HitEffect->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_HitEffect->SetAutoActivate(false);
	m_HitEffect->bAutoDestroy = true;

	m_HitAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("HitAudio"));
	m_HitAudio->SetupAttachment(m_HitEffect);
}

// Called when the game starts or when spawned
void AMeson_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeson_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeson_Projectile::StopProjectile(const FHitResult& ImpactResult)
{
	Destroy();
}

void AMeson_Projectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AMeson_Projectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AMeson_Projectile::SetLocation(const FVector& Loc)
{
	if(IsValid(m_DefaultHitSphere))
		m_DefaultHitSphere->SetWorldLocation(Loc);
}

void AMeson_Projectile::SetRotation(const FRotator& Rot)
{
	if (IsValid(m_DefaultHitSphere))
		m_DefaultHitSphere->SetWorldRotation(Rot);
}
