// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAIAnimInstance.h"
#include "AuroraAICharacter.h"
#include "../../Effect/DefaultEffect.h"

UAuroraAIAnimInstance::UAuroraAIAnimInstance()
{
	m_AnimType = EAIAnimType::Start;

	m_AttackIndex = 0;

	m_AttackEnable = true;
}

void UAuroraAIAnimInstance::PlayStart()
{
	m_AnimType = EAIAnimType::Start;

	if (m_AnimType != EAIAnimType::Start || Montage_IsPlaying(m_StartMontage))
	{
		return;
	}

	Montage_SetPosition(m_StartMontage, 0.f);

	Montage_Play(m_StartMontage);
}

void UAuroraAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAuroraAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UAuroraAIAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UAuroraAIAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UAuroraAIAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UAuroraAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		for (int i = 0; i < m_Skill.Num(); i++)
		{
			Aurora->SetSkillCoolTime(m_Skill[i].CurCoolTime, m_Skill[i].MaxCoolTime, m_Skill[i].IsCool);
		}
	}

	PlayStart();
}

void UAuroraAIAnimInstance::TestSkill(int Index)
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (Montage_IsPlaying(m_SkillMontage[Index]) || !IsValid(Aurora) || Aurora->GetIsCool(Index) || !m_AttackEnable || m_AnimType == EAIAnimType::Attack)
	{
		return;
	}

	m_AttackEnable = false;

	m_AnimType = EAIAnimType::Skill1;

	Montage_SetPosition(m_SkillMontage[Index], 0.f);

	Montage_Play(m_SkillMontage[Index]);

	Aurora->UseSkill(Index);
}

void UAuroraAIAnimInstance::Attack()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (m_AnimType != EAIAnimType::Attack || Montage_IsPlaying(m_AttackMontage[m_AttackIndex]) || !m_AttackEnable)
	{
		return;
	}

	m_AttackEnable = false;

	Montage_SetPosition(m_AttackMontage[m_AttackIndex], 0.f);

	Montage_Play(m_AttackMontage[m_AttackIndex]);

	m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontage.Num();
}

void UAuroraAIAnimInstance::AnimNotify_Attack()
{
}

void UAuroraAIAnimInstance::AnimNotify_AttackEnd()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->SetAttackEnd(true);
	}

	m_AttackEnable = true;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), m_AttackEnable));
}

void UAuroraAIAnimInstance::AnimNotify_StartEnd()
{
	m_AnimType = EAIAnimType::Idle;

	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->SetStartEnd(true);
	}
}

void UAuroraAIAnimInstance::AnimNotify_StartEffect()
{
	
}

void UAuroraAIAnimInstance::AnimNotify_AuroraDash()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		//Aurora->Dash();
	}
}

void UAuroraAIAnimInstance::AnimNotify_DassStart()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->SetDass(true);
		Aurora->SetCollisionEnable();
	}
}

void UAuroraAIAnimInstance::AnimNotify_DassEnd()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->SetDass(false);
		Aurora->SetCollisionEnable();
	}
}

void UAuroraAIAnimInstance::AnimNotify_AuroraFreeze()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->Freeze();
	}
}

void UAuroraAIAnimInstance::AnimNotify_FreezeEnd()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->SetAttackEnd(true);
	}

	m_AttackEnable = true;

	//m_AnimType = EAIAnimType::Idle;
}

void UAuroraAIAnimInstance::AnimNotify_AuroraUltimate()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->Ultimate();
	}
}

void UAuroraAIAnimInstance::AnimNotify_AuroraDeath()
{
	AAuroraAICharacter* Aurora = Cast<AAuroraAICharacter>(TryGetPawnOwner());

	if (IsValid(Aurora))
	{
		Aurora->Death();
	}
}
