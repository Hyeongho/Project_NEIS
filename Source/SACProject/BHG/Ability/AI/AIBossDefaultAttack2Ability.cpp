// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossDefaultAttack2Ability.h"
#include "../../Component/AbilityComponent.h"
#include "../../Animation/BHG_AIBossAnimInstance.h"
#include "../../AI/AI_BossMonster.h"
#include "../../Collider/HitBoxObject.h"
#include "../../Player/BHG_Player.h"

UAIBossDefaultAttack2Ability::UAIBossDefaultAttack2Ability() : 
	Super()
{
	m_AbilityName = TEXT("AIBossDefaultAttack2");
}

void UAIBossDefaultAttack2Ability::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(OwnerComp->GetOwner());

	if (m_AbilityActive)
	{

		if (IsValid(BossCharacter))
		{
			UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(BossCharacter->GetMesh()->GetAnimInstance());

			if (IsValid(BossAnim))
			{
				BossAnim->DefaultAttack2();
			}

			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();

		}
	}
}

void UAIBossDefaultAttack2Ability::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("DefaultAttack2CounterStart"))
	{
		//Owner의 상태를 카운터상태로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(true);

	}

	else if (EventName == TEXT("DefaultAttack2CounterEnd"))
	{
		//Owner의 상태를 카운터비활성화로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(false);
	}

	else if (EventName == TEXT("CreateDefaultAttack1HitBox"))
	{
		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
		{

			if (IsValid(m_AbilityHitBox))
			{
				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ActorParam.Owner = BossCharacter;

				FVector OwnerFwdLoc = BossCharacter->GetActorForwardVector();
				OwnerFwdLoc *= 250.f;

				m_AbilityHitBoxObj = GetWorld()->SpawnActor<AHitBoxObject>(m_AbilityHitBox,
					BossCharacter->GetActorLocation() + OwnerFwdLoc,
					FRotator::ZeroRotator, ActorParam);

				m_AbilityHitBoxObj->SetShooter(BossCharacter);

			}
		}
	}

	else if (EventName == TEXT("DestroyDefaultAttack1HitBox"))
	{
		m_AbilityHitBoxObj->HitBoxDestroy();
	}

	else if (EventName == TEXT("DamagedBossDefaultAttack2"))
	{
		ABHG_Player* BHGPlayer = Cast<ABHG_Player>(Target);

		if (IsValid(BHGPlayer))
			BHGPlayer->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}
}

void UAIBossDefaultAttack2Ability::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
}

void UAIBossDefaultAttack2Ability::AbilityActiveOn()
{
	Super::AbilityActiveOn();

	GetWorld()->GetTimerManager().ClearTimer(m_AbilityTimerHandle);
}

void UAIBossDefaultAttack2Ability::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UAIBossDefaultAttack2Ability::AbilityActiveOn, m_AbilityCoolTime, false);
}
