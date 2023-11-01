// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_ThunderStormCol.h"
#include "Components/BoxComponent.h"
#include "../../../AI/AICharacter.h"

// Sets default values
AKwang_ThunderStormCol::AKwang_ThunderStormCol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetBoxExtent(FVector(500.0, 500.0, 150.0));
	
	m_Damage = 50;
}

// Called when the game starts or when spawned
void AKwang_ThunderStormCol::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKwang_ThunderStormCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKwang_ThunderStormCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);

	if(AICharacter)
		AICharacter->TakeDamage(m_Damage, FDamageEvent(), nullptr, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AKwang_ThunderStormCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

