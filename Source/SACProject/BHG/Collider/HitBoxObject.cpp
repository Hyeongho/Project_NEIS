// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBoxObject.h"


// Sets default values
AHitBoxObject::AHitBoxObject()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Counter = false;

	m_DefaultHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DefaultHitBox"));

	SetRootComponent(m_DefaultHitBox);

	m_DefaultHitBox->SetBoxExtent(FVector(30.0, 30.0, 30.0));	

	m_DefaultHitBox->SetGenerateOverlapEvents(true);

	m_DefaultHitBox->bHiddenInGame = false;

	//BeginOverlap Delegate
	m_DefaultHitBox->OnComponentBeginOverlap.AddDynamic(this, &AHitBoxObject::HitBoxBeginOverlap);

	//EndOverlap Delegate
	m_DefaultHitBox->OnComponentEndOverlap.AddDynamic(this, &AHitBoxObject::HitBoxEndOverlap);
}

void AHitBoxObject::SetCollisionProfile(const FName& ProfileName)
{
	m_DefaultHitBox->SetCollisionProfileName(ProfileName);
}

void AHitBoxObject::SetShooter(ACharacter* Shooter)
{
	m_Shooter = Shooter;
}
// Called when the game starts or when spawned
void AHitBoxObject::BeginPlay()
{
	Super::BeginPlay();

	if (m_MinDamage == m_MaxDamage)
		m_TrueDamage = m_MaxDamage;

	else
		m_TrueDamage = FMath::RandRange(m_MinDamage, m_MaxDamage);
	
}

// Called every frame
void AHitBoxObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitBoxObject::HitBoxDestroy()
{
	//하위클래스별로 구현할것

}

void AHitBoxObject::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 하위클래스에서 구현할것 

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());
}

void AHitBoxObject::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 하위클래스에서 구현할것 

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());
}

