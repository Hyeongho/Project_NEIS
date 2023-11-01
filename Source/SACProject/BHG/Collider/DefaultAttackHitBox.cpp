// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAttackHitBox.h"
#include "../Effect/BaseEffect.h"
#include "../Animation/BHG_AIAnimInstance.h"
#include "../AI/AI_Monster.h"
#include "../Component/AbilityComponent.h"

ADefaultAttackHitBox::ADefaultAttackHitBox()
	: Super()
{
	m_MaxDamage = 50;
	m_MinDamage = 10;
}

void ADefaultAttackHitBox::HitBoxDestroy()
{
	Super::HitBoxDestroy();

	Destroy();
}

void ADefaultAttackHitBox::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());

}

void ADefaultAttackHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultAttackHitBox::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	FVector HitLoc = SweepResult.ImpactPoint;	

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABaseEffect>(m_Effect, GetActorLocation(), GetActorRotation(), ActorParam);

	m_Target = Cast<ACharacter>(OtherActor);	

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 
		
		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedDefaultAttack"), m_Shooter, m_Target, m_TrueDamage);
		}
	}	
	

}

void ADefaultAttackHitBox::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
