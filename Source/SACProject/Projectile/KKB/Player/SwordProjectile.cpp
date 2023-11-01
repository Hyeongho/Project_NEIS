// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../../AI/AICharacter.h"
#include "NiagaraComponent.h"

// Sets default values
ASwordProjectile::ASwordProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_DefaultHitSphere->SetCollisionProfileName("PlayerAttackOverlap");
	m_DefaultHitSphere->SetSphereRadius(48.f);


	m_SwordProj = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjParticle"));
	m_SwordProj->SetupAttachment(RootComponent);
	m_SwordProj->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));


	m_Damage = 23;


	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ParticleAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/KKB/Texture/EnergyBall/N_EnergySphere.N_EnergySphere'"));

	if (ParticleAsset.Succeeded())
		m_SwordProj->SetAsset(ParticleAsset.Object);


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));

	if (ParticleAsset2.Succeeded())
		m_HitEffect->SetTemplate(ParticleAsset2.Object);
}

void ASwordProjectile::Shoot(float Size)
{
	// 0차지 : 1배
	// 1차지 : 1.5배
	// 2차지 : 2.25배
	m_DefaultHitSphere->SetWorldScale3D(m_DefaultHitSphere->GetRelativeScale3D() * Size);

	m_Damage *= Size;
}

// Called when the game starts or when spawned
void ASwordProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(10.f);
}

// Called every frame
void ASwordProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwordProjectile::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ASwordProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


	// 타격한 적에게 데미지
	AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);

	if (AICharacter) {
		AICharacter->TakeDamage(m_Damage, FDamageEvent(), nullptr, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

		if (IsValid(m_HitEffect))
			m_HitEffect->Activate();

		if (IsValid(m_HitAudio))
			m_HitAudio->Play();
	}


}
