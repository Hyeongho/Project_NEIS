// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowingEffect.h"

AFollowingEffect::AFollowingEffect()
	: Super()
{
	m_FollowSocket = false;
	m_SocketName = TEXT("");
}

void AFollowingEffect::BeginPlay()
{
	Super::BeginPlay();


}

void AFollowingEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Effect�� Owner�� �ִ��� Ȯ��. 
	if (IsValid(m_Owner))
	{
		// Owner�� ����������Ʈ����? Owner�� Socket�� ������ ����Ʈ���� ?

		if (m_FollowSocket)
		{
			//Owner�� Socket�� �����Ѵ�. 
			FVector SocketLoc = m_Owner->GetMesh()->GetSocketLocation(m_SocketName);
			SetActorLocation(SocketLoc);
		}

		else
		{
			//Owner�� �����Ѵ�.  

			m_Offset = m_Owner->GetActorForwardVector() * 120.f * -1.f;

			SetActorLocation(m_Owner->GetActorLocation() + m_Offset);	
			SetActorRotation(m_Owner->GetActorRotation());
		}

	}

	//Owner�� ���ٸ� ����Ʈ�� �����Ѵ�. 
	else
		Destroy();


}
