// Fill out your copyright notice in the Description page of Project Settings.


#include "NightmareProjectie.h"
#include "../Player/BHG_Player.h"
#include "../AI/DefaultAICharacter.h"
#include "../Effect/BaseEffect.h"
#include "../Component/AbilityComponent.h"

ANightmareProjectie::ANightmareProjectie() 
	: Super()
{
	m_Box->SetBoxExtent(FVector(30.0, 30.0, 30.0));

	m_TargetDetect = false;

	m_ProjectieSpeed = 2000.f;

	m_Box->SetNotifyRigidBodyCollision(false);
	m_Box->SetGenerateOverlapEvents(true);

	m_Length = 1000.f;

	m_MaxDamage = 50;
	m_MinDamage = 10;



}

void ANightmareProjectie::BeginPlay()
{
	Super::BeginPlay();

	if (m_MinDamage == m_MaxDamage)
		m_TrueDamage = m_MaxDamage;

	else
		m_TrueDamage = FMath::RandRange(m_MinDamage, m_MaxDamage);


	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());

	int32 ElementCount = m_Mesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* TMaterial = m_Mesh->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(TMaterial);
	}

	if (IsValid(this))
	{
		for (auto& Mtrl : mMaterialArray)
		{		
			Mtrl->SetVectorParameterValue(TEXT("Color"), FVector(0.0,1.0,0.0));
			Mtrl->SetScalarParameterValue(TEXT("Opacity"), 3.f);
		}
	}


}

void ANightmareProjectie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (IsValid(this))
	{
		if (!m_TargetDetect)
			m_Mesh->AddWorldRotation(FRotator(0.0, 720.f * DeltaTime, 0.0));


		if (!m_TargetDetect)
		{
			m_Length -= m_ProjectieSpeed * DeltaTime;

			if (m_Length <= 0.f)
				Destroy();
		}

		else
		{
			float CapsuleHalfHeight = m_Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			FVector TargetLoc = m_Target->GetActorLocation();
			TargetLoc.Z += CapsuleHalfHeight * 3.f;
			SetActorLocation(TargetLoc);
		}
	}

}

void ANightmareProjectie::ProjectileFire(FVector Velocity, ACharacter* Shooter)
{
	Super::ProjectileFire(Velocity, Shooter);
}

void ANightmareProjectie::OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHitEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ANightmareProjectie::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ProjectileBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	m_TargetDetect = true;

	m_Target = Cast<ACharacter>(OtherActor);

	if (IsValid(m_Target))
	{
		float CapsuleHalfHeight = m_Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		FVector TargetLoc = m_Target->GetActorLocation();

		TargetLoc.Z += CapsuleHalfHeight * 3.f;

		m_Move->Velocity = FVector(0.0,0.0,0.0);

		m_Mesh->SetWorldRotation(FRotator(180.0, 0.0, 0.0));
		SetActorLocation(TargetLoc);



		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ABaseEffect>(m_ProjectileEffect, SweepResult.Location, FRotator::ZeroRotator, ActorParam);


		if (IsValid(m_Target) && IsValid(m_Shooter))
		{
			//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 

			UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

			if (IsValid(AbilityComp))
			{
				AbilityComp->ActivatedAbilityEvent(TEXT("DamagedNightmare"), m_Shooter, m_Target, m_TrueDamage);
			}
		}

	}
}
