// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BossMonster.h"
#include "../Component/AbilityComponent.h"
#include "../Animation/BHG_AIBossAnimInstance.h"
#include "BHG_AIBossController.h"
#include "BHG_AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../AI/AIState.h"
#include "../Effect/BaseEffect.h"
#include "../../UI/CJH/DamageTextWidget.h"
#include "../GameMode/BHG_GameMode.h"
#include "../UI/BossHpWidget.h"

AAI_BossMonster::AAI_BossMonster()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABHG_AIBossController::StaticClass();

	//Ability Setting
	m_Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("AIAbility"));
	m_Ability->SetPlayer(false);

	CounterAttackState = false;

	m_Name = TEXT("RamPage");

	BossGlowEnable = false;

	RespawnOn = false;
	RespawnTime = 0.f;

	AbilityEnable = true;
	BossDie = false;

	StartEnable = false;

	AbilityTime = 0.f;
}

void AAI_BossMonster::SetRespawnOn()
{
	RespawnOn = true;
	GetCharacterMovement()->GravityScale = 1.f;
}

void AAI_BossMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAI_BossMonster::BeginPlay()
{
	Super::BeginPlay();

	FAIDataTable* Data = new FAIDataTable;
	Data->HP = 1000;
	Data->MP = 100;
	Data->ArmorPoint = 10;
	Data->AttackPoint = 50;
	Data->MoveSpeed = 450.f;
	Data->AttackDistance = 250.f;
	Data->InteractionDistance = 2000.f;

	m_AIState->SetInfo("Rampage", Data);;

	if (IsValid(m_Ability))
	{
		m_Ability->GiveAbility(m_DefaultAttack);
		m_Ability->GiveAbility(m_DefaultAttack2);
		m_Ability->GiveAbility(m_Skill1);
		m_Ability->GiveAbility(m_Skill2);
	}

	//Material Setting
	int32 ElementCount = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* TMaterial = GetMesh()->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(TMaterial);
	}

	GetCharacterMovement()->MaxWalkSpeed = 450.f;

}

void AAI_BossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TestAbilityOn)
	{
		AbilityTime += DeltaTime;

		if (AbilityTime > 1.f)
		{
			AbilityEnable = true;
			TestAbilityOn = false;
			AbilityTime = 0.f;
		}
	}


	if (!StartEnable)
	{

		if (GetCharacterMovement()->IsMovingOnGround())
		{
			FVector DownLoc = GetActorUpVector() * -200.f;

			GetWorld()->SpawnActor<ABaseEffect>(m_CutSceneEffect, GetActorLocation() + DownLoc, GetActorRotation());
			StartEnable = true;
		}


	}


	if (BossGlowEnable)
	{
		GlowTime += DeltaTime;

		if (GlowTime > 0.3f)
		{
			for (auto& Mtrl : mMaterialArray)
			{
				Mtrl->SetScalarParameterValue(TEXT("GlowEnable"), 0.f);		
				GlowTime = 0.f;
				BossGlowEnable = false;
			}
		}
	}

}

void AAI_BossMonster::OnDamaged(int32 Damage, ACharacter* Shooter, ACharacter* Target, bool Counter)
{
	Super::OnDamaged(Damage, Shooter, Target, Counter);

	//먼저 현재 카운터상태인지 확인. 

	if (CounterAttackState)
	{
		// 현재 카운터상태라면, 들어온 공격이 카운터공격인지 확인한다. 
		if (Counter)
		{
			//들어온 공격이 카운터공격이라면 , Animation을 변경해야하므로 Animation쪽으로 카운터가 성공했음을 알려줘야한다. 
			//먼저 공격자가 앞에서 공격했을때만 카운터 공격으로 간주해야한다. 

			if (IsValid(Shooter) && IsValid(Target))
			{
				float DotValue = FVector::DotProduct(Shooter->GetActorForwardVector(),
					Target->GetActorForwardVector());

				//내적하였을때 값이 -가 되어야 앞에 있다고 볼수 있으므로 이경우에만 카운터를 성공으로 간주한다. 
				if (DotValue < 0)
				{
					UBHG_AIBossAnimInstance* BossAnim = Cast<UBHG_AIBossAnimInstance>(GetMesh()->GetAnimInstance());
					BossAnim->SetCounterSuccess(true);

					CounterAttackState = false;

					if (IsValid(m_CounterSuccessEffect))
					{

						FVector BossFwdLoc = GetActorForwardVector() * 100.f;

						GetWorld()->SpawnActor<ABaseEffect>(m_CounterSuccessEffect, GetActorLocation() + BossFwdLoc, GetActorRotation());
					}

					for (auto& Mtrl : mMaterialArray)
					{
						Mtrl->SetScalarParameterValue(TEXT("GlowEnable"), 1.f);
						Mtrl->SetVectorParameterValue(TEXT("GlowColor"), FVector(0.7, 0.0, 0.0));

						BossGlowEnable = true;
					}
				}
			}	
		}
		
	}

	ABHG_GameMode* GMode = Cast<ABHG_GameMode>(GetWorld()->GetAuthGameMode());

	m_AIState->SetDamage(Damage);

	UBossHpWidget* BossBar = GMode->GetBossHpBar();

	float MaxHp = m_AIState->GetHPMax();
	float CurHp = m_AIState->GetHP();

	float Value = CurHp / MaxHp;

	BossBar->SetBarValue(Value);	


	if (IsValid(m_DamageTextWidgetClass))
	{
		UDamageTextWidget* DamageWidget = CreateWidget<UDamageTextWidget>(GetWorld(), m_DamageTextWidgetClass);
		if (IsValid(DamageWidget))
		{
			DamageWidget->AddToViewport();
			DamageWidget->SetDamageText(Damage, Target->GetActorLocation());


			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D ScreenPosition;
			PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
			DamageWidget->SetPositionInViewport(ScreenPosition);
		}
	}


	if (0 >= m_AIState->GetHP())
	{
		BossDie = true;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UBHG_AIBossAnimInstance* Anim = Cast<UBHG_AIBossAnimInstance>(GetMesh()->GetAnimInstance());
		Anim->SetAnimType(EAIBossMonsterAnimType::Die);

		ABHG_AIBossController* BossController = Cast<ABHG_AIBossController>(Controller);

		if (BossController)
			BossController->UnPossess();

		for (auto& Mtrl : mMaterialArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("GlowEnable"), 0.f);		
		}

		if (IsValid(GMode))
			GMode->PortalStart();

	}


	


}

void AAI_BossMonster::BossDefaultAttack()
{
	if (AbilityEnable)
	{
		m_Ability->ActivatedAbility(TEXT("AIBossDefaultAttack1"));
		AbilityEnable = false;
	}	
}

void AAI_BossMonster::BossDefaultAttack2()
{

	if (AbilityEnable)
	{
		m_Ability->ActivatedAbility(TEXT("AIBossDefaultAttack2"));
		AbilityEnable = false;
	}
}

void AAI_BossMonster::BossSkill1()
{
	if (AbilityEnable)
	{

		m_Ability->ActivatedAbility(TEXT("AIBossSkill1"));
		AbilityEnable = false;
	}
}

void AAI_BossMonster::BossSKill2()
{
	if (AbilityEnable)
	{

		m_Ability->ActivatedAbility(TEXT("AIBossSkill2"));
		AbilityEnable = false;
	}
}

void AAI_BossMonster::SetCharacterGlow(FVector Color, bool GlowEnable)
{
	for (auto& Mtrl : mMaterialArray)
	{

		if (GlowEnable)
		{
			Mtrl->SetScalarParameterValue(TEXT("GlowEnable"), 1.f);
			Mtrl->SetVectorParameterValue(TEXT("GlowColor"), FVector(Color));
		}

		else
		{
			Mtrl->SetScalarParameterValue(TEXT("GlowEnable"), 0.f);
			Mtrl->SetVectorParameterValue(TEXT("GlowColor"), FVector(Color));
		}
	}
}

void AAI_BossMonster::BossAbilityEnd()
{
	//AbilityEnable = true;

	TestAbilityOn = true;
}

const bool& AAI_BossMonster::GetBossAbilityEnable()
{
	return AbilityEnable;
}


