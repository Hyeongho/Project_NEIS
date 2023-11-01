// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerObject.h"

ATriggerObject::ATriggerObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	SetRootComponent(m_Body);


#if UE_BUILD_DEBUG
	m_Body->bVisualizeComponent = true;
#endif

	m_Body->SetBoxExtent(FVector(100.0, 100.0, 100.0));

	m_Body->SetCollisionProfileName(TEXT("AISpawnTrigger"));

	m_Body->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	m_Body->OnComponentBeginOverlap.AddDynamic(this, &ATriggerObject::OverlapBegin);
}

void ATriggerObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ATriggerObject::BeginPlay()
{
	Super::BeginPlay();
}

void ATriggerObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerObject::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATriggerObject::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
