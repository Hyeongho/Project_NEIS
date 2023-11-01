// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_DefaultAttackAbility.h"
#include "../../Component/AbilityComponent.h"
#include "../../Animation/BHG_AIAnimInstance.h"
#include "../../AI/AI_Monster.h"
#include "../../Collider/HitBoxObject.h"
#include "../../Player/BHG_Player.h"

UAI_DefaultAttackAbility::UAI_DefaultAttackAbility()
	: Super()
{
	m_AbilityName = TEXT("AIDefaultAttack");
}

void UAI_DefaultAttackAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	AAI_Monster* MonsterCharacter = Cast<AAI_Monster>(OwnerComp->GetOwner());

	if (IsValid(MonsterCharacter))
	{
		UBHG_AIAnimInstance* MonsterAnim = Cast<UBHG_AIAnimInstance>(MonsterCharacter->GetMesh()->GetAnimInstance());

		if (IsValid(MonsterAnim))
		{
			MonsterAnim->AIDefaultAttack();
		}
	}

}

void UAI_DefaultAttackAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("CreateDefaultHitBox"))
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);

		if (IsValid(OwnerCharacter))
		{	
			
			if (IsValid(m_AbilityHitBox))
			{
						FActorSpawnParameters	ActorParam;
						ActorParam.SpawnCollisionHandlingOverride =
							ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						ActorParam.Owner = OwnerCharacter;
						
						FVector OwnerFwdLoc = OwnerCharacter->GetActorForwardVector();
						OwnerFwdLoc *= 150.f;				

						m_AbilityHitBoxObj = GetWorld()->SpawnActor<AHitBoxObject>(m_AbilityHitBox,
							OwnerCharacter->GetActorLocation() + OwnerFwdLoc,
							FRotator::ZeroRotator, ActorParam);		
				
			}
		}
	}

	else if (EventName == TEXT("DestroyDefaultHitBox"))
	{
		if (IsValid(m_AbilityHitBoxObj))
			m_AbilityHitBoxObj->HitBoxDestroy();
	}

	else if (EventName == TEXT("DamagedAIDefaultAttack"))
	{
		ABHG_Player* BHGPlayer = Cast<ABHG_Player>(Target);

		if (IsValid(BHGPlayer))
			BHGPlayer->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}



}

void UAI_DefaultAttackAbility::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
}

void UAI_DefaultAttackAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();
}

void UAI_DefaultAttackAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();
}
