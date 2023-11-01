// Fill out your copyright notice in the Description page of Project Settings.



#include "AIBossDefaultAttackHitBox.h"
#include "../Component/AbilityComponent.h"

AAIBossDefaultAttackHitBox::AAIBossDefaultAttackHitBox() :
	Super()
{
}

void AAIBossDefaultAttackHitBox::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());
}

void AAIBossDefaultAttackHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIBossDefaultAttackHitBox::HitBoxDestroy()
{
	Super::HitBoxDestroy();

	Destroy();
}

void AAIBossDefaultAttackHitBox::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HitBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	m_Target = Cast<ACharacter>(OtherActor);

	if (!IsValid(m_Shooter))
		m_Shooter = Cast<ACharacter>(GetOwner());

	if (IsValid(m_Target) && IsValid(m_Shooter))
	{
		//�浹�� �����Ͽ��ٸ� , ������ó���� ���� �����Ƽ �̺�Ʈ�� �߻���Ų��. 

		UAbilityComponent* AbilityComp = m_Shooter->GetComponentByClass<UAbilityComponent>();

		if (IsValid(AbilityComp))
		{
			AbilityComp->ActivatedAbilityEvent(TEXT("DamagedBossDefaultAttack"), m_Shooter, m_Target, m_TrueDamage);
		}
	}
}

void AAIBossDefaultAttackHitBox::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::HitBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
