// Fill out your copyright notice in the Description page of Project Settings.


#include "TerraAnimInstance.h"
#include "TerraCharacter.h"

UTerraAnimInstance::UTerraAnimInstance()
{
	m_AttackIndex = 0;
	m_AttackEnable = true;
}

void UTerraAnimInstance::Attack()
{
	if (!m_AttackEnable || Montage_IsPlaying(m_AttackMontage[m_AttackIndex]))
	{
		return;
	}

	m_AttackEnable = false;

	Montage_SetPosition(m_AttackMontage[m_AttackIndex], 0.f);

	Montage_Play(m_AttackMontage[m_AttackIndex]);

	m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontage.Num();
}

void UTerraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UTerraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ATerraCharacter* Player = Cast<ATerraCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			m_MoveSpeed = Movement->Velocity.Length();
		}
	}
}

void UTerraAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UTerraAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UTerraAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UTerraAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UTerraAnimInstance::GuradIntro()
{
	m_AnimType = ETerraAnimType::Gurad;
}

void UTerraAnimInstance::Skill(int Index)
{
	if (Montage_IsPlaying(m_SkillMontage[Index]))
	{
		return;
	}

	m_AnimType = ETerraAnimType::Skill;

	Montage_SetPosition(m_SkillMontage[Index], 0.f);

	Montage_Play(m_SkillMontage[Index]);
}

void UTerraAnimInstance::AnimNotify_Attack()
{
	ATerraCharacter* Player = Cast<ATerraCharacter>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->Attack();
	}
}

void UTerraAnimInstance::AnimNotify_AttackEnable()
{
	m_AttackEnable = true;
}

void UTerraAnimInstance::AnimNotify_AttackEnd()
{
	m_AttackIndex = 0;
}

void UTerraAnimInstance::AnimNotify_GuradStart()
{
	m_AnimType = ETerraAnimType::Gurad;
}

void UTerraAnimInstance::AnimNotify_PrintEffect()
{
}

void UTerraAnimInstance::AnimNotify_SkillEnd()
{
	m_AnimType = ETerraAnimType::Default;
}
