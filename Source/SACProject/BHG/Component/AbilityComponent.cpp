// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "../Ability/DefaultAttackAbility.h"
#include "../Ability/ShurikenAttackAbility.h"
#include "../Player/BHG_Player.h"
#include "../Animation/BHG_PlayerAnimInstance.h"
#include "../Player/BHG_ShadowPlayer.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
	: Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	m_PlayerForwardSpeed = 0.f;
	m_PlayerRightSpeed = 0.f;

	m_Abilitys.Empty();

	m_Player = false;
	m_MoveOn = true;	

}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Owner Only Player
	if (m_Player)
	{
		ACharacter* BHGPlayer = Cast<ACharacter>(GetOwner());

		if (IsValid(BHGPlayer))
		{

			UCharacterMovementComponent* Movement = BHGPlayer->GetCharacterMovement();

			if (IsValid(Movement))
			{

				FVector PlayerForward = BHGPlayer->GetActorForwardVector();

				float PlayerForwardSpeed = FVector::DotProduct(Movement->Velocity, PlayerForward);

				m_PlayerForwardSpeed = PlayerForwardSpeed * 1.f;


				FVector PlayerRight = BHGPlayer->GetActorRightVector();

				float PlayerRightSpeed = FVector::DotProduct(Movement->Velocity, PlayerRight);

				m_PlayerRightSpeed = PlayerRightSpeed * -1.f;

				//현재 플레이어가 이동상태인지를 판단한다. 
				// 상하좌우의 속도가 0이 아니라면 움직이는 상태이다. 
				if (m_PlayerForwardSpeed != 0.f || m_PlayerRightSpeed != 0.f)
					m_MoveOn = false;

				else
					m_MoveOn = true;

			}

		}
	}
}

UDefaultAbility* UAbilityComponent::FindAbility(const FName& AbilityName)
{

	for (int32 i = 0; i < m_Abilitys.Num(); ++i)
	{
		if (m_Abilitys[i]->GetAbilityName() == AbilityName)
			return m_Abilitys[i];
	}

	return nullptr;
}

float UAbilityComponent::GetPlayerForwardSpeed()
{
	return m_PlayerForwardSpeed;
}

float UAbilityComponent::GetPlayerRightSpeed()
{
	return m_PlayerRightSpeed;
}

void UAbilityComponent::GiveAbility(TSubclassOf<UDefaultAbility> Ability)
{	
		
	if (IsValid(Ability))
	{
		UDefaultAbility* NewAbility = NewObject<UDefaultAbility>(this, Ability);	

			if (NewAbility)
			{
				m_Abilitys.Add(NewAbility);			
			}
	}
}

void UAbilityComponent::ActivatedAbility(FName AbilityName)
{

	if (m_Abilitys.Num())
	{

		for (int32 i = 0; i < m_Abilitys.Num(); ++i)
		{
			// 어빌리티의 실행부, 등록된 어빌리티의 이름을 먼저 탐색.
			if (m_Abilitys[i]->GetAbilityName() == AbilityName)
			{
				ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

				//어빌리티 실행
				if (m_Player)
				{

					m_Abilitys[i]->ActivatedAbility(this, OwnerCharacter->GetMesh()->GetAnimInstance());
				}

				else
					m_Abilitys[i]->ActivatedAbility(this, OwnerCharacter->GetMesh()->GetAnimInstance());

				break;
			}
		}
	}
}

void UAbilityComponent::EndAbility(FName AbilityName)
{
	UDefaultAbility* Ability = FindAbility(AbilityName);

	if (IsValid(Ability))
	{
		Ability->EndAbility(this);		
	}
}

void UAbilityComponent::ActivatedAbilityEvent(FName EventName, APawn* Owner, APawn* Target, int32 Value)
{
	for (int32 i = 0; i < m_Abilitys.Num(); ++i)
	{
		m_Abilitys[i]->ActivatedAbilityEvent(EventName, Owner, Target, Value);
	}
}

