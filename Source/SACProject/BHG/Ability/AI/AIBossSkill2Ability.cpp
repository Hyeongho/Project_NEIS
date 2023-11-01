// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossSkill2Ability.h"
#include "../../Component/AbilityComponent.h"
#include "../../Animation/BHG_AIBossAnimInstance.h"
#include "../../AI/AI_BossMonster.h"
#include "../../Decal/DecalBase.h"
#include "../../Effect/BaseEffect.h"
#include "../../Collider/HitBoxObject.h"
#include "../../Player/BHG_Player.h"


UAIBossSkill2Ability::UAIBossSkill2Ability()
	: Super()
{
	m_AbilityName = TEXT("AIBossSkill2");
}

void UAIBossSkill2Ability::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
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
				BossAnim->Skill2();
			}


			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();
		}
	}
}

void UAIBossSkill2Ability::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);


	if (EventName == TEXT("DecalCreate"))
	{
		if (IsValid(m_WarningDecal))
		{
			FVector DownLoc = Owner->GetActorUpVector() * -170.f;
			FVector FwdLoc = Owner->GetActorForwardVector() * 200.f;

			GetWorld()->SpawnActor<ADecalBase>(m_WarningDecal, Owner->GetActorLocation()+ DownLoc + FwdLoc, Owner->GetActorRotation());
		}
	}

	else if (EventName == TEXT("CreateSkill2HitBox"))
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

			if (IsValid(m_Effect))
			{

				FVector FwdLoc = BossCharacter->GetActorForwardVector();
				FwdLoc *= 200.f;

				FVector DownLoc = BossCharacter->GetActorUpVector() * -1.f;
				DownLoc *= 190.f;

					GetWorld()->SpawnActor<ABaseEffect>(m_Effect, BossCharacter->GetActorLocation() + FwdLoc + DownLoc,
						BossCharacter->GetActorRotation());
			}
			
		}
	}

	else if (EventName == TEXT("DestroySkill2HitBox"))
	{
		if (IsValid(m_AbilityHitBoxObj))
			m_AbilityHitBoxObj->HitBoxDestroy();
	}

	else if (EventName == TEXT("DamagedBossSkill2"))
	{
		ABHG_Player* BHGPlayer = Cast<ABHG_Player>(Target);

		if (IsValid(BHGPlayer))
			BHGPlayer->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}

}

void UAIBossSkill2Ability::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
}

void UAIBossSkill2Ability::AbilityActiveOn()
{
	Super::AbilityActiveOn();

	GetWorld()->GetTimerManager().ClearTimer(m_AbilityTimerHandle);
}

void UAIBossSkill2Ability::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UAIBossSkill2Ability::AbilityActiveOn, m_AbilityCoolTime, false);
}
