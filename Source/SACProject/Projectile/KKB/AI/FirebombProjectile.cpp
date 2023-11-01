// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebombProjectile.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"

AFirebombProjectile::AFirebombProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_DefaultHitSphere->SetCollisionProfileName("AIAttackOverlap");


	m_Movement->InitialSpeed = 1000.f; // 초기 발사 속도 설정
	m_Movement->MaxSpeed = 1000.f; // 최대 속도 설정
	m_Movement->bRotationFollowsVelocity = true;
	m_Movement->ProjectileGravityScale = 0.f;
	m_Movement->bShouldBounce = true; // 장애물과 충돌 시 반사 여부
	m_Movement->Bounciness = 0.3f; // 반사 계수



	// Proj Base Particle Setting
	m_FirebombProj = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjParticle"));
	m_FirebombProj->SetupAttachment(RootComponent);
	m_FirebombProj->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//m_ParticleSystem->SetAutoActivate(false);
	//m_ParticleSystem->bAutoDestroy = true;
	

	m_Damage = 5;



	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonIggyScorch/FX/Particles/IggyScorch/Abilities/Primary/FX/P_IggyScorch_Projectile_Trail.P_IggyScorch_Projectile_Trail'"));

	if (ParticleAsset.Succeeded())
		m_FirebombProj->SetTemplate(ParticleAsset.Object);


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonIggyScorch/FX/Particles/IggyScorch/Abilities/Primary/FX/P_IggyScorch_Projectile_HitPlayer.P_IggyScorch_Projectile_HitPlayer'"));

	if (ParticleAsset2.Succeeded())
		m_HitEffect->SetTemplate(ParticleAsset2.Object);
}

void AFirebombProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(15.f);
}

void AFirebombProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirebombProjectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AFirebombProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


	AKwang_PlayerCharacter* PlayerCharacter = Cast<AKwang_PlayerCharacter>(OtherActor);

	if (IsValid(PlayerCharacter)) {
		if (IsValid(m_FirebombProj))
			m_FirebombProj->Deactivate();

		if (IsValid(m_HitEffect))
			m_HitEffect->Activate(true);

		if (IsValid(m_HitAudio))
			m_HitAudio->Play();

		PlayerCharacter->TakeDamage(m_Damage, FDamageEvent(), nullptr, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	}
}
