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

			//���� �ִϸ��̼� ������ �����ѻ������� ���� Ȯ��. �ִϸ��̼� ����ó���Ŀ� ��Ÿ���� �����ؾ��Ѵ�. 
			bool AttackEnable = Cast<UBHG_PlayerAnimInstance>(AnimInstance)->GetAttackEnable();
			//���� �÷��̾ �̵������� Ȯ���Ѵ�. 
			bool MoveEnable = OwnerComp->GetMoveEnable();

			//�ٸ��ִϸ��̼��� �����ϰ� �ְų�, �̵����̶�� �����Ƽ�� �������� �ʴ´�. 
			if (!AttackEnable || !MoveEnable)
				return;

			FVector OwnerLoc = OwnerComp->GetOwner()->GetActorLocation();
			FRotator OwnerRot = OwnerComp->GetOwner()->GetActorRotation();

			// �÷��̾� ���� ��ġ�� ���Ѵ�. 
			FVector OwnerBackVec = OwnerComp->GetOwner()->GetActorForwardVector() * -1.f;
			OwnerBackVec *= 40.f;

			// �÷��̾� �������� �׸��ڸ� ��ȯ�Ѵ�. 
			APlayerCharacter* Shadow = GetWorld()->SpawnActor<APlayerCharacter>(m_Shadow, OwnerLoc + OwnerBackVec, OwnerRot);

			ABHG_Player* Player = Cast<ABHG_Player>(OwnerComp->GetOwner());

			//�÷��̾�� �׸��ڿ��� ���� ����
			Player->SetShadowPlayer(Cast<ABHG_ShadowPlayer>(Shadow));
			Cast<ABHG_ShadowPlayer>(Shadow)->SetPlayer(Player);

			m_AbilityActive = false;

			//��Ÿ���� ����Ѵ�. 
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
