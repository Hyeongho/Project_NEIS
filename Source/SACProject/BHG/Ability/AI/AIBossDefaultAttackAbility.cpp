// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossDefaultAttackAbility.h"
#include "../../Component/AbilityComponent.h"
#include "../../Animation/BHG_AIBossAnimInstance.h"
#include "../../AI/AI_BossMonster.h"
#include "../../Collider/HitBoxObject.h"
#include "../../Player/BHG_Player.h"

UAIBossDefaultAttackAbility::UAIBossDefaultAttackAbility()
	: Super()
{
	m_AbilityName = TEXT("AIBossDefaultAttack1");
}

void UAIBossDefaultAttackAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(OwnerComp->GetOwner());

	if (IsValid(BossCharacter))
	{
		UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(BossCharacter->GetMesh()->GetAnimInstance());

		if (IsValid(BossAnim))
		{
			BossAnim->DefaultAttack1();
		}
	}
}

void UAIBossDefaultAttackAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("DefaultAttack1CounterStart"))
	{
		//Owner의 상태를 카운터상태로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(true);

	}

	else if (EventName == TEXT("DefaultAttack1CounterEnd"))
	{
		//Owner의 상태를 카운터비활성화로 변경한다. 

		AAI_BossMonster* BossCharacter = Cast<AAI_BossMonster>(Owner);

		if (IsValid(BossCharacter))
			BossCharacter->SetCounterState(false);
	}

	else if (EventName == TEXT("CreateDefaultAttackHitBox"))
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

	else if (EventName == TEXT("DestroyDefaultAttackHitBox"))
	{
		if(IsValid(m_AbilityHitBoxObj))
		m_AbilityHitBoxObj->HitBoxDestroy();
	}

	else if (EventName == TEXT("DamagedBossDefaultAttack"))
	{
		ABHG_Player* BHGPlayer = Cast<ABHG_Player>(Target);

		if (IsValid(BHGPlayer))
			BHGPlayer->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}

}

void UAIBossDefaultAttackAbility::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
}

void UAIBossDefaultAttackAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();
}

void UAIBossDefaultAttackAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

}
