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
		//Nightmare ��ų�� ó�� ����Ҷ��� �ִϸ��̼��� �����Ѵ�. 
		//��ų�� ����ߴٸ� ����Ʈ�޾ �������������, �ִϸ��̼��� ���۵����ʵ��� ���´�.  
		if (!m_NightmareOn)
		{

			//���� �ִϸ��̼� ������ �����ѻ������� ���� Ȯ��. �ִϸ��̼� ����ó���Ŀ� ��Ÿ���� �����ؾ��Ѵ�. 
			bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();

			//���� �÷��̾ �̵������� Ȯ���Ѵ�. 
			bool MoveEnable = OwnerComp->GetMoveEnable();

			//�ٸ��ִϸ��̼��� �����ϰ� �ְų�, �̵����̶�� �����Ƽ�� �������� �ʴ´�. 
			if (!AttackEnable || !MoveEnable)
				return;

			//�����Ƽ ����߿� �̵��̾ȵǵ��� ���´�. 
			OwnerComp->SetMoveLockEnable(true);

			//���� �����ѻ��¶�� �ִϸ��̼��� �����ϰ�, ��Ÿ���� �����Ѵ�. 
			Cast<UBHG_PlayerAnimInstance>(AnimInstance)->NightmareAttack();	

			m_AbilityActive = false;

			//��Ÿ���� ����Ѵ�. 
			AbilityCoolTimeActivated();
		}

	
	}

	//����Ʈ�޾ Ÿ�ٿ��� ����������, ��ȿ������ ��� �����Ƽ�� �����Ǹ� �÷��̾ Ÿ���� �ڷ� �̵����Ѿ��Ѵ�. 
	if (IsValid(m_NightmareObj))
	{
		//���� Ÿ���� ������������ Ȯ���Ѵ�. 
		m_SelectTarget = Cast<ANightmareProjectie>(m_NightmareObj)->GetTargetDetect();

		if (m_SelectTarget)
		{
			//Ÿ���� ��ġ
			FVector MonsterLoc = m_NightmareObj->GetTargetActor()->GetActorLocation();

			//Ÿ�����η� ���ϴ� ����
			FVector TargetAxis = m_NightmareObj->GetTargetActor()->GetActorLocation() - m_NightmareObj->GetShooterActor()->GetActorLocation();
			TargetAxis.Normalize();
			TargetAxis *= 100.f;

			FVector MonsterDownLoc = m_NightmareObj->GetTargetActor()->GetActorUpVector() * -25.f;

			//Animation�� �����Ѵ�. 
			UBHG_PlayerAnimInstance* PlayerAnim = Cast<UBHG_PlayerAnimInstance>(AnimInstance);

			if (IsValid(PlayerAnim))
			{
				PlayerAnim->SetAnimType(EBHGPlayerAninType::Nightmare);
			}

			//Ÿ���� �ڷ� �÷��̾� �̵�
			m_NightmareObj->GetShooterActor()->SetActorLocation(MonsterLoc + TargetAxis + MonsterDownLoc);

			//Ÿ���� ��ġ�� �̵��Ͽ����� ����Ʈ�޾������Ʈ�� �������Ѿ��Ѵ�. 
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
		// Damage�� ���� ��󿡰� ����. 		
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
	
	//�����Ƽ�� ����Ǹ� �̵��� �����ϵ��� �Ѵ�. 	
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

	//��Ÿ�� ����� ����Ʈ�޾� ����
	if (IsValid(m_NightmareObj))
	{
		m_NightmareObj->Destroy();
		m_NightmareOn = false;
		m_NightmareObj = nullptr;
	}
	// ���� ��Ÿ������ÿ� ���� if���� ���ư����ʴ´ٸ� ����Ʈ�޾ �������� �����Ȼ����̹Ƿ�, �ٽ� ����Ҽ� �ֵ��� �Ѵ�. 
	else 
	{
		m_NightmareOn = false;
		m_NightmareObj = nullptr;
	}
}
