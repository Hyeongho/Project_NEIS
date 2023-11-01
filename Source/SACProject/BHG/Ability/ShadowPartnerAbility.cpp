// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPartnerAbility.h"
#include "../Player/BHG_ShadowPlayer.h"
#include "../Player/BHG_Player.h"
#include "../Component/AbilityComponent.h"
#include "../Animation/BHG_PlayerAnimInstance.h"

UShadowPartnerAbility::UShadowPartnerAbility()
	: Super()
{
	m_AbilityName = TEXT("ShadowPartner");
}

void UShadowPartnerAbility::ActivatedAbility(UAbilityComponent* OwnerComp, UAnimInstance* AnimInstance)
{
	Super::ActivatedAbility(OwnerComp, AnimInstance);

	if (m_AbilityActive)
	{

		if (IsValid(m_Shadow))
		{

			//현재 애니메이션 변경이 가능한상태인지 먼저 확인. 애니메이션 변경처리후에 쿨타임을 적용해야한다. 
			bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();
			//현재 플레이어가 이동중인지 확인한다. 
			bool MoveEnable = OwnerComp->GetMoveEnable();

			//다른애니메이션이 동작하고 있거나, 이동중이라면 어빌리티를 실행하지 않는다. 
			if (!AttackEnable || !MoveEnable)
				return;

			FVector OwnerLoc = OwnerComp->GetOwner()->GetActorLocation();
			FRotator OwnerRot = OwnerComp->GetOwner()->GetActorRotation();

			// 플레이어 뒤쪽 위치를 구한다. 
			FVector OwnerBackVec = OwnerComp->GetOwner()->GetActorForwardVector() * -1.f;
			OwnerBackVec *= 40.f;

			// 플레이어 뒤쪽으로 그림자를 소환한다. 
			APlayerCharacter* Shadow = GetWorld()->SpawnActor<APlayerCharacter>(m_Shadow, OwnerLoc + OwnerBackVec, OwnerRot);

			ABHG_Player* Player = Cast<ABHG_Player>(OwnerComp->GetOwner());

			//플레이어와 그림자에게 각각 전달
			Player->SetShadowPlayer(Cast<ABHG_ShadowPlayer>(Shadow));
			Cast<ABHG_ShadowPlayer>(Shadow)->SetPlayer(Player);

			m_AbilityActive = false;

			//쿨타임을 등록한다. 
			AbilityCoolTimeActivated();

		}
	}
}

void UShadowPartnerAbility::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	Super::ActivatedAbilityEvent(EventName, Owner, Target, Value);
}

void UShadowPartnerAbility::AbilityActiveOn()
{
	Super::AbilityActiveOn();

}

void UShadowPartnerAbility::AbilityCoolTimeActivated()
{
	Super::AbilityCoolTimeActivated();

	GetWorld()->GetTimerManager().SetTimer(m_AbilityTimerHandle, this, &UShadowPartnerAbility::AbilityActiveOn, m_AbilityCoolTime, false);


}
