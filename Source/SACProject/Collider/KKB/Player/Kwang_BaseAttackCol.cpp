// Fill out your copyright notice in the Description page of Project Settings.


#include "Kwang_BaseAttackCol.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../../AI/AICharacter.h"

// Sets default values
AKwang_BaseAttackCol::AKwang_BaseAttackCol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox->SetBoxExtent(FVector(125.f, 125.f, 75.f));

	m_Damage = 25;
}

// Called when the game starts or when spawned
void AKwang_BaseAttackCol::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKwang_BaseAttackCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKwang_BaseAttackCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);

	if (AICharacter)
		AICharacter->TakeDamage(m_Damage, FDamageEvent(), nullptr, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AKwang_BaseAttackCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

