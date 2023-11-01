// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalObject.h"

// Sets default values
APortalObject::APortalObject() : 
	Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PortalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalBox"));
	m_PortalEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticle"));


	SetRootComponent(m_PortalBox);
	m_PortalEffect->SetupAttachment(m_PortalBox);

	m_PortalBox->SetBoxExtent(FVector(100.0, 100.0, 100.0));

	m_PortalBox->SetGenerateOverlapEvents(true);

	m_PortalBox->OnComponentBeginOverlap.AddDynamic(this, &APortalObject::PortalBeginOverlap);

	m_LevelName = TEXT("");

}

// Called when the game starts or when spawned
void APortalObject::BeginPlay() 
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalObject::PortalBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(m_LevelName.IsValid())
		UGameplayStatics::OpenLevel(GetWorld(), m_LevelName);

}

