// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkill1Object.h"
#include "../Projectile/BossRockProjectile.h"
#include "../Decal/WarningDecal.h"

// Sets default values
ABossSkill1Object::ABossSkill1Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossSkill1Object::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(WarningDecal))
	{
		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ActorParam.Owner = this;

		AWarningDecal* Decal = GetWorld()->SpawnActor<AWarningDecal>(WarningDecal, GetActorLocation(), GetActorRotation(), ActorParam);
	}


	
}

// Called every frame
void ABossSkill1Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossSkill1Object::DecalEnd()
{
	if (IsValid(RockProjectile))
	{
		FVector ActorUPLoc = GetActorUpVector() * 500.f;

		AProjectileBase* RockProj = GetWorld()->SpawnActor<AProjectileBase>(RockProjectile, GetActorLocation() + ActorUPLoc,
			GetActorRotation());

		FVector DownVelocity = GetActorUpVector() * -1.f;

		RockProj->ProjectileFire(DownVelocity, Cast<ACharacter>(GetOwner()));
	}

	Destroy();

}

