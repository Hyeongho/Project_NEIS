// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADefaultItem::ADefaultItem()
	: Super()
	, m_ItemName(TEXT("DefaultItem"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	m_CollisionBox->SetCollisionProfileName(TEXT("Item"));
	m_CollisionBox->SetGenerateOverlapEvents(true);
	m_CollisionBox->SetNotifyRigidBodyCollision(true);
	m_CollisionBox->SetupAttachment(GetRootComponent());
	SetRootComponent(m_CollisionBox);

	m_ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	m_ItemMesh->SetSimulatePhysics(false);
	m_ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_ItemMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

