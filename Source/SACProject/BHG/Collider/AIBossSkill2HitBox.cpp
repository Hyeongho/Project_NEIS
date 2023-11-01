// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossSkill2HitBox.h"
#include "../Component/AbilityComponent.h"

AAIBossSkill2HitBox::AAIBossSkill2HitBox()
	:Super()
{
}

void AAIBossSkill2HitBox::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());
}

void AAIBossSkill2HitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIBossSkill2HitBox::HitBoxDestroy()
{
	Super::HitBoxDestroy();

	Destroy();
}

void AAIBossSkill2HitBox::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	m_Target = Cast<ACharacter>(OtherActor);

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//충돌이 성공하였다면 , 데미지처리를 위해 어빌리티 이벤트를 발생시킨다. 

		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedBossSkill2"), m_Shooter, m_Target, m_TrueDamage);
		}
	}
}

void AAIBossSkill2HitBox::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
