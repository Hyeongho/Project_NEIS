// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Monster.h"
#include "../Component/AbilityComponent.h"
#include "../Animation/BHG_AIAnimInstance.h"
#include "BHG_AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../AI/AIState.h"
#include "../SpawnObject/MonsterSpawnObject.h"
#include "../Effect/BaseEffect.h"
#include "Components/WidgetComponent.h"
#include "../../UI/CJH/DamageTextWidget.h"

AAI_Monster::AAI_Monster()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	//Ability Setting
	m_Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("AIAbility"));
	m_Ability->SetPlayer(false);

	m_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MonsterWidget"));
	m_Widget->SetupAttachment(GetRootComponent());

	

	//m_Name = TEXT("Grux");

	HitOn = false;

	AIControllerClass = ABHG_AIController::StaticClass();

	RespawnOn = false;
	RespawnTime = 0.f;



	
}

void AAI_Monster::SetSpawner(AMonsterSpawnObject* OwnerSpawn)
{
	m_Spawner = OwnerSpawn;
}

void AAI_Monster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


}

void AAI_Monster::BeginPlay()
{
	Super::BeginPlay();

	FAIDataTable* Data = new FAIDataTable;
	Data->HP = 200;
	Data->MP = 100;
	Data->ArmorPoint = 10;
	Data->AttackPoint = 30;
	Data->MoveSpeed = 200.f;
	Data->AttackDistance = 100.f;
	Data->InteractionDistance = 800.f;

	m_AIState->SetInfo("Grux", Data);

	GetCharacterMovement()->MaxWalkSpeed = Data->MoveSpeed;

	if (IsValid(m_Ability))
	{
		m_Ability->GiveAbility(m_DefaultAttack);
	}

	//Material Setting
	int32 ElementCount = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* TMaterial = GetMesh()->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(TMaterial);
	}
	

}

void AAI_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!RespawnOn)
	{
		RespawnTime += DeltaTime;

		if (RespawnTime > 1.3f)
		{
			RespawnOn = true;

			RespawnTime = 0.f;
			GetCharacterMovement()->GravityScale = 1.f;
		}

	}

	if (HitOn)
	{
		HitTime += DeltaTime;

		for (auto& Mtrl : mMaterialArray)
		{
			Mtrl->SetVectorParameterValue(TEXT("HitColor"), FVector(0.8, 0.1, 0.0));
		}

		if (HitTime > 0.5f)
		{
			HitOn = false;
			HitTime = 0.f;
			for (auto& Mtrl : mMaterialArray)
			{
				Mtrl->SetVectorParameterValue(TEXT("HitColor"), FVector(0.0, 0.0, 0.0));
			}
		}
	}

}

void AAI_Monster::OnDamaged(int32 Damage, ACharacter* Shooter, ACharacter* Target, bool Counter)
{
	Super::OnDamaged(Damage, Shooter, Target, Counter);

	//데미지 후처리 .
	//플레이어쪽을 바라보게 만든다. 
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), Shooter->GetActorLocation());
	Target->SetActorRotation(LookAtRotation);

	UBHG_AIAnimInstance* AIAnim = Cast<UBHG_AIAnimInstance>(Target->GetMesh()->GetAnimInstance());
	AIAnim->SetHitEnable(true);

	m_AIState->SetDamage(Damage);

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

	float MaxHP = m_AIState->GetHPMax();
	float CurrentHP = m_AIState->GetHP();

	float Value = CurrentHP / MaxHP;

	Cast<UProgressBar>(m_Widget->GetWidget()->GetWidgetFromName(TEXT("MonsterBar")))->SetPercent(Value);

	if (Value <= 0.f)
	{
		//Cast<UProgressBar>(m_Widget->GetWidget()->GetWidgetFromName(TEXT("MonsterBar")))->SetVisibility(ESlateVisibility::Hidden);

		m_Widget->SetVisibility(false);
	}

	if (0 >= m_AIState->GetHP())
	{
		AIAnim->SetAnimType(EAIMonsterAnimType::Die);		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		int32 Min = 0;
		int32 Max = 10;

		int32 RandomValue = FMath::RandRange(Min, Max);

		if (RandomValue < 3)
		{		
			FVector DownLoc = GetActorUpVector() * -50.f;
			GetWorld()->SpawnActor<ABaseEffect>(m_HealItem, GetActorLocation() + DownLoc, GetActorRotation());
		}

		if(IsValid(m_Spawner))
		m_Spawner->MonsterDie();
	}

	if (!HitOn)
		HitOn = true;

}

void AAI_Monster::DefaultAttack()
{	
	m_Ability->ActivatedAbility(TEXT("AIDefaultAttack"));
}
