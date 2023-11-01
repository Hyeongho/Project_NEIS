// Fill out your copyright notice in the Description page of Project Settings.


#include "ShurikenAttackAbility.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Projectile/ProjectileBase.h"
#include "../AI/DefaultAICharacter.h"

UShurikenAttackAbility::UShurikenAttackAbility()
	: Super()
{
	m_AbilityName = TEXT("ShurikenAttack");
}

void UShurikenAttackAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp,AnimInstance);

	Cast<UBHG_PlayerAnimInstance>(AnimInstance)->ShurikenAttack();
}

void UShurikenAttackAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);


	if (EventName == TEXT("ShurikenCreate"))
	{
		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AProjectileBase* Proj = GetWorld()->SpawnActor<AProjectileBase>(m_Shuriken,Owner->GetActorLocation(), 
			Owner->GetActorRotation(), ActorParam);

		Proj->ProjectileFire(Owner->GetActorForwardVector(), Cast<ACharacter>(Owner));

	}

	else if (EventName == TEXT("DamagedShuriken"))
	{
		// Damage를 받을 대상에게 전달. 		
		ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

		if (IsValid(AITarget))
			AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}


}

void UShurikenAttackAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();
}
