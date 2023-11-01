// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAttackAbility.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Component/AbilityComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "../Collider/HitBoxObject.h"
#include "../AI/DefaultAICharacter.h"

UDefaultAttackAbility::UDefaultAttackAbility()
	: Super()
{
	m_AbilityName = TEXT("DefaultAttack");

	m_CounterAbility = true;
}

void UDefaultAttackAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp,AnimInstance);

	if (m_AbilityActive)
	{	


			Cast<UBHG_PlayerAnimInstance>(AnimInstance)->DefaultAttack();

			
	}

}

void UDefaultAttackAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("CreateDefaultHitBox"))
	{


		ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);

		if (IsValid(OwnerCharacter))
		{
			USkeletalMeshComponent* OwnerSkelComp = OwnerCharacter->GetMesh();

			if (IsValid(OwnerSkelComp))
			{
				const USkeletalMeshSocket* WeaponSocket = OwnerSkelComp->GetSocketByName(TEXT("Weapon_Socket"));

				if (IsValid(WeaponSocket))
				{
					if (IsValid(m_AbilityHitBox))
					{
						FActorSpawnParameters	ActorParam;
						ActorParam.SpawnCollisionHandlingOverride =
							ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

						ActorParam.Owner = OwnerCharacter;
				

						m_AbilityHitBoxObj = GetWorld()->SpawnActor<AHitBoxObject>(m_AbilityHitBox,
							WeaponSocket->GetSocketLocation(OwnerSkelComp),
							FRotator::ZeroRotator, ActorParam);	
				
						m_AbilityHitBoxObj->SetShooter(OwnerCharacter);
					

						if (IsValid(m_AbilityHitBoxObj))
							WeaponSocket->AttachActor(m_AbilityHitBoxObj, OwnerSkelComp);
					}
				}
			}
		}
	}

	else if (EventName == TEXT("DestroyDefaultHitBox"))
	{
		if (IsValid(m_AbilityHitBoxObj))
			m_AbilityHitBoxObj->HitBoxDestroy();
	}


	else if (EventName == TEXT("DamagedDefaultAttack"))
	{
		// Damage를 받을 대상에게 전달. 		
		ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

		if (IsValid(AITarget))
			AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
		
	}

		
}

void UDefaultAttackAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();
}

void UDefaultAttackAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();
}
