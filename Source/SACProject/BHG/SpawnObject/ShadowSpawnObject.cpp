// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowSpawnObject.h"
#include "../Player/BHG_UltimateShadow.h"
#include "../Projectile/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

AShadowSpawnObject::AShadowSpawnObject()
	: Super()
{
	m_ShadowOffset = 1.f;

	m_SkillStart = false;

	m_SkillTime = 0.f;
}

void AShadowSpawnObject::BeginPlay()
{
	Super::BeginPlay();

	//SpawnObject 중심으로 그림자를 세팅한다. 

	FVector ActorFwdLoc = GetActorForwardVector();
	FVector ActorBackLoc = ActorFwdLoc * -1.f;

	FVector ActorRightLoc = GetActorRightVector();	
	FVector ActorLeftLoc = ActorRightLoc * -1.f;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 앞 
	ABHG_UltimateShadow* Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow,
		GetActorLocation() + ActorFwdLoc * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//뒤
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + ActorBackLoc * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//좌
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + ActorLeftLoc * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//우
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + ActorRightLoc * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);	

	m_ShadowOffset -= 50.f;

	//우상단 
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + (ActorRightLoc
		+ ActorFwdLoc) * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//우하단 
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + (ActorRightLoc
		+ ActorBackLoc) * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//좌상단
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + (ActorLeftLoc
		+ ActorFwdLoc) * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);

	//좌하단
	Shadow = GetWorld()->SpawnActor<ABHG_UltimateShadow>(m_UltimateShadow, GetActorLocation() + (ActorLeftLoc
		+ ActorBackLoc) * m_ShadowOffset,
		FRotator::ZeroRotator, ActorParam);
	Shadow->SetOwnerActor(this);


	m_ProjectieNum = m_UltimateProjectile.Num();

}

void AShadowSpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_SkillStart)
	{
		if (m_UltimateProjectile.Num() && IsValid(this))
		{
			m_SkillTime += DeltaTime;

			if (m_SkillTime > 0.03f)
			{
				// 칼소환 오브젝트 위에 
				FVector ActorUpLoc = GetActorUpVector();
				ActorUpLoc *= 400.f;

				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				float RandomXValue = FMath::RandRange(-100.f, 100.f);
				float RandomYValue = FMath::RandRange(-100.f, 100.f);

				FVector OriginLoc = GetActorLocation();
				OriginLoc.X += RandomXValue;
				OriginLoc.Y += RandomYValue;

				int32 RandomIndex = FMath::RandRange(0, m_ProjectieNum - 1);

				AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(m_UltimateProjectile[RandomIndex],
					OriginLoc + ActorUpLoc, FRotator::ZeroRotator, ActorParam);

				FRotator RandomRotation;
				RandomRotation.Yaw = FMath::RandRange(-180.0f, 180.0f);

				Projectile->SetActorRotation(RandomRotation);

	

				//아래로 떨어지도록 velocity 지정 .

				FVector DownAxis = GetActorUpVector() * -1.f;

				APlayerController* CurrentPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

				Projectile->ProjectileFire(DownAxis, Cast<ACharacter>(CurrentPlayerController->GetPawn()));

				m_SkillTime = 0.f;
			}
		}
	}

}

void AShadowSpawnObject::UltimateSkillStart()
{
	m_SkillStart = true;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector DownLoc = GetActorUpVector() * -100.f;

	GetWorld()->SpawnActor<ABaseEffect>(m_AuraEffect, GetActorLocation() + DownLoc, GetActorRotation(), ActorParam);

}

void AShadowSpawnObject::SpawnerDestory()
{
	Destroy();
}

void AShadowSpawnObject::SpawnerEffect()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector DownLoc = GetActorUpVector() * -100.f;

	GetWorld()->SpawnActor<ABaseEffect>(m_UltimateEffect, GetActorLocation() + DownLoc, GetActorRotation(), ActorParam);
}
