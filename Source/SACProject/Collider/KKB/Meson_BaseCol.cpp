// Fill out your copyright notice in the Description page of Project Settings.


#include "Meson_BaseCol.h"

// Sets default values
AMeson_BaseCol::AMeson_BaseCol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_DefaultHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	SetRootComponent(m_DefaultHitBox);

	m_DefaultHitBox->SetGenerateOverlapEvents(true);

#if UE_BUILD_DEBUG
	m_DefaultHitBox->bHiddenInGame = false;
#endif

	// 델리게이트 설정
	m_DefaultHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeson_BaseCol::HitBoxBeginOverlap);
	m_DefaultHitBox->OnComponentEndOverlap.AddDynamic(this, &AMeson_BaseCol::HitBoxEndOverlap);
}

// Called when the game starts or when spawned
void AMeson_BaseCol::BeginPlay()
{
	Super::BeginPlay();

	// LifeTime을 0.5초로 설정
	SetLifeSpan(0.5f);
}

// Called every frame
void AMeson_BaseCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeson_BaseCol::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AMeson_BaseCol::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

