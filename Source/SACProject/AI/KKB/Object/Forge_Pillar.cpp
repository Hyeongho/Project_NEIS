// Fill out your copyright notice in the Description page of Project Settings.


#include "Forge_Pillar.h"
#include "../Grux_AICharacter.h"
#include "../../../Player/KKB/Kwang_PlayerCharacter.h"

AForge_Pillar::AForge_Pillar()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Component
	m_Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");

	SetRootComponent(m_Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/InfinityBladeFireLands/Environments/Fire/Env_Fire_OddsnEnds/StaticMesh/SM_Env_Fire_OddsnEnds_Pillar1.SM_Env_Fire_OddsnEnds_Pillar1'"));

	if (MeshAsset.Succeeded())
		m_Body->SetStaticMesh(MeshAsset.Object);

	m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// Collision Component
	m_BoxCol = CreateDefaultSubobject<UBoxComponent>("BoxCol");
	m_BoxCol->SetupAttachment(RootComponent);
	m_BoxCol->SetBoxExtent(FVector(80.0, 80.0, 170.0));
	m_BoxCol->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	m_BoxCol->SetCollisionProfileName("BlockAll");

	m_BoxCol->OnComponentHit.AddDynamic(this, &AForge_Pillar::OnHit);
	m_BoxCol->OnComponentBeginOverlap.AddDynamic(this, &AForge_Pillar::HitBoxBeginOverlap);
}

void AForge_Pillar::BeginPlay()
{
	Super::BeginPlay();
}

void AForge_Pillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AForge_Pillar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(OtherActor);

	// 온힛 한 것이 그럭스라면 스턴 상태로.
	if (IsValid(GruxCharacter)) 
		GruxCharacter->SetStun();
}

void AForge_Pillar::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

