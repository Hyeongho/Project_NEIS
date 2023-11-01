// Fill out your copyright notice in the Description page of Project Settings.


#include "NightmareAbility.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Projectile/ProjectileBase.h"
#include "../Projectile/NightmareProjectie.h"
#include "../Component/AbilityComponent.h"
#include "../AI/DefaultAICharacter.h"
#include "../Effect/BaseEffect.h"
#include "../Collider/HitBoxObject.h"

UNightmareAbility::UNightmareAbility()
	: Super()
{
	m_AbilityName = (TEXT("Nightmare"));

	m_NightmareOn = false;
}

void UNightmareAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	

	if (m_AbilityActive)
	{
		//Nightmare 스킬을 처음 사용할때만 애니메이션을 변경한다. 
		//스킬을 사용했다면 나이트메어가 사라지기전까지, 애니메이션이 동작되지않도록 막는다.  
		if (!m_NightmareOn)
		{

			//현재 애니메이션 변경이 가능한상태인지 먼저 확인. 애니메이션 변경처리후에 쿨타임을 적용해야한다. 
			bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

			//현재 플레이어가 이동중인지 확인한다. 
			bool MoveEnable = OwnerComp->GetMoveEnable();

			//다른애니메이션이 동작하고 있거나, 이동중이라면 어빌리티를 실행하지 않는다. 
			if (!AttackEnable || !MoveEnable)
				return;

			//어빌리티 사용중에 이동이안되도록 막는다. 
			OwnerComp->SetMoveLockEnable(true);

			//변경 가능한상태라면 애니메이션을 변경하고, 쿨타임을 적용한다. 
			Cast<UBHG_PlayerAnimInstance>(AnimInstance)->NightmareAttack();	

			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();
		}

	
	}

	//나이트메어가 타겟에게 적중했으며, 유효상태일 경우 어빌리티가 재실행되면 플레이어를 타겟의 뒤로 이동시켜야한다. 
	if (IsValid(m_NightmareObj))
	{
		//현재 타겟이 맞은상태인지 확인한다. 
		m_SelectTarget = Cast<ANightmareProjectie>(m_NightmareObj)->GetTargetDetect();

		if (m_SelectTarget)
		{
			//타겟의 위치
			FVector MonsterLoc = m_NightmareObj->GetTargetActor()->GetActorLocation();

			//타겟으로로 향하는 방향
			FVector TargetAxis = m_NightmareObj->GetTargetActor()->GetActorLocation() - m_NightmareObj->GetShooterActor()->GetActorLocation();
			TargetAxis.Normalize();
			TargetAxis *= 100.f;

			FVector MonsterDownLoc = m_NightmareObj->GetTargetActor()->GetActorUpVector() * -25.f;

			//Animation을 변경한다. 
			UBHG_PlayerAnimInstance* PlayerAnim = Cast<UBHG_PlayerAnimInstance>(AnimInstance);

			if (IsValid(PlayerAnim))
			{
				PlayerAnim->SetAnimType(EBHGPlayerAninType::Nightmare);
			}

			//타겟의 뒤로 플레이어 이동
			m_NightmareObj->GetShooterActor()->SetActorLocation(MonsterLoc + TargetAxis + MonsterDownLoc);

			//타겟의 위치로 이동하였으면 나이트메어오브젝트를 삭제시켜야한다. 
			m_NightmareObj->Destroy();
			m_NightmareOn = false;

			
			if (IsValid(m_NightmareEffect))
			{
				FVector OwnerDownLoc = OwnerComp->GetOwner()->GetActorUpVector() * -100.f;


				FHitResult HitResult;
				FVector Start = OwnerComp->GetOwner()->GetActorLocation(); 
				FVector End = Start - FVector(0, 0, 500.0); 

				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(OwnerComp->GetOwner()); 
				CollisionParams.AddIgnoredActor(m_SelectTarget);

				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldDynamic, CollisionParams))
				{
				
					FVector SpawnLocation = HitResult.ImpactPoint; 				
					GetWorld()->SpawnActor<ABaseEffect>(m_NightmareEffect, SpawnLocation,
						OwnerComp->GetOwner()->GetActorRotation());

				}
				/*



				GetWorld()->SpawnActor<ABaseEffect>(m_NightmareEffect, OwnerComp->GetOwner()->GetActorLocation() + OwnerDownLoc,
					OwnerComp->GetOwner()->GetActorRotation());*/
			}

			if (IsValid(m_AbilityHitBox))
			{
				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ActorParam.Owner = OwnerComp->GetOwner();

				GetWorld()->SpawnActor<AHitBoxObject>(m_AbilityHitBox, OwnerComp->GetOwner()->GetActorLocation(),
					OwnerComp->GetOwner()->GetActorRotation(), ActorParam);
			}
			

		}
	}


}

void UNightmareAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);

	if (EventName == TEXT("NightmareStart"))
	{
		m_NightmareOn = true;
	}

	else if (EventName == TEXT("NightmareCreate"))
	{
		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ActorParam.Owner = Owner;

		m_NightmareObj = GetWorld()->SpawnActor<AProjectileBase>(m_Nightmare, Owner->GetActorLocation(),
			Owner->GetActorRotation(), ActorParam);

		FVector OwnerFwd = Owner->GetActorForwardVector();

		m_NightmareObj->ProjectileFire(OwnerFwd, Cast<ACharacter>(Owner));
	}

	else if (EventName == TEXT("DamagedNightmare"))
	{
		// Damage를 받을 대상에게 전달. 		
		ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

		if (IsValid(AITarget))
			AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}


	else if (EventName == TEXT("DamagedNightmareBackAttack"))
	{
		ADefaultAICharacter* AITarget = Cast<ADefaultAICharacter>(Target);

		if (IsValid(AITarget))
			AITarget->OnDamaged(Value, Cast<ACharacter>(Owner), Cast<ACharacter>(Target), m_CounterAbility);
	}

}

void UNightmareAbility::EndAbility(UAbilityComponent* OwnerComp)
{
	Super::EndAbility(OwnerComp);
	
	//어빌리티가 종료되면 이동이 가능하도록 한다. 	
	OwnerComp->SetMoveLockEnable(false);
}

void UNightmareAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UNightmareAbility::AbilityActiveOn, m_AbilityCoolTime, false);
		
}

void UNightmareAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();

	//쿨타임 종료시 나이트메어 삭제
	if (IsValid(m_NightmareObj))
	{
		m_NightmareObj->Destroy();
		m_NightmareOn = false;
		m_NightmareObj = nullptr;
	}
	// 만약 쿨타임종료시에 위에 if문에 돌아가지않는다면 나이트메어가 빗나가고 삭제된상태이므로, 다시 사용할수 있도록 한다. 
	else 
	{
		m_NightmareOn = false;
		m_NightmareObj = nullptr;
	}
}
