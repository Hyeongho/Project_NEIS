// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileRoot"));
	m_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ProjectileMesh"));
	m_Move = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));	

	m_Box->SetNotifyRigidBodyCollision(true);
	m_Box->OnComponentHit.AddDynamic(this, &AProjectileBase::OnComponentHitEvent);

	m_Box->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::ProjectileBeginOverlap);

	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_Mesh->SetEnableGravity(false);

	SetRootComponent(m_Box);

	m_Mesh->SetupAttachment(m_Box);

	m_Move->SetUpdatedComponent(m_Box);

	m_Move->ProjectileGravityScale = 0.f;

	m_ProjectieSpeed = 1000.f;	

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProjectileFire(FVector Velocity, ACharacter* Shooter)
{
	m_Shooter = Shooter;

	m_Move->Velocity = Velocity * m_ProjectieSpeed;
}

void AProjectileBase::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//하위클래스에서 구현할것
}

void AProjectileBase::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//하위클래스에서 구현할것
}



