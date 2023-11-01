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


	// Effect의 Owner가 있는지 확인. 
	if (IsValid(m_Owner))
	{
		// Owner를 추적할이펙트인지? Owner의 Socket을 추적할 이펙트인지 ?

		if (m_FollowSocket)
		{
			//Owner의 Socket을 추적한다. 
			FVector SocketLoc = m_Owner->GetMesh()->GetSocketLocation(m_SocketName);
			SetActorLocation(SocketLoc);
		}

		else
		{
			//Owner를 추적한다.  

			m_Offset = m_Owner->GetActorForwardVector() * 120.f * -1.f;

			SetActorLocation(m_Owner->GetActorLocation() + m_Offset);	
			SetActorRotation(m_Owner->GetActorRotation());
		}

	}

	//Owner가 없다면 이펙트를 삭제한다. 
	else
		Destroy();


}
