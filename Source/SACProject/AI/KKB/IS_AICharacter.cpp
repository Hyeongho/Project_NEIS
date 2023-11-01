// Fill out your copyright notice in the Description page of Project Settings.


#include "IS_AICharacter.h"
#include "IS_AIAnimInst.h"
#include "IS_AIController.h"
#include "../AIState.h"
#include "../../Projectile/KKB/AI/FirebombProjectile.h"
#include "../../Component/KKB/CoolDownComponent.h"
#include "../../UI/CJH/DamageTextWidget.h"
#include "Components/WidgetComponent.h"

AIS_AICharacter::AIS_AICharacter() :
	m_IsElite(false)
{
	PrimaryActorTick.bCanEverTick = true;

	// �޽� �ּ� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonIggyScorch/Characters/Heroes/IggyScorch/Skins/Fireball/Meshes/IggyScorch_Fireball.IggyScorch_Fireball'"));

	if (MeshAsset.Succeeded()) 
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);


	// ĸ�� ������Ʈ ����
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	GetCapsuleComponent()->SetCollisionProfileName("AI");

	// �޽� ����
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));


	// �ִϸ��̼� �������Ʈ ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/KKB/AI/IggyScorch/Anim/AB_IS.AB_IS_C'"));

	if (AnimClass.Succeeded()) 
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);


	// ���� ��ٿ� ������Ʈ ����
	m_AttackCooldownComp = CreateDefaultSubobject<UCoolDownComponent>(TEXT("AttackCooldown"));


	// ���� ������Ʈ ����
	m_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ISHPBarWidget"));
	m_Widget->SetupAttachment(GetRootComponent());
	m_Widget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BP_MonsterHP.BP_MonsterHP_C'"));

	if(WidgetClass.Succeeded())
		m_Widget->SetWidgetClass(WidgetClass.Class);

	m_Widget->SetDrawSize(FVector2D(100, 10));


	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass2(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/CJH/Blueprints/Widget/W_DamageText.W_DamageText_C'"));

	if(WidgetClass2.Succeeded())
		m_DamageTextWidgetClass = WidgetClass2.Class;



	// AI Controller ����
	AIControllerClass = AIS_AIController::StaticClass();


	// Dissolve ����
	m_DissCurTime = 0.f;
	m_DissTime = 1.5f;
	m_DissEnable = false;

	// ��Ÿ ���� ����
	FAIDataTable* Data = new FAIDataTable;
	Data->HP = 50;
	Data->AttackPoint = 30;
	Data->MoveSpeed = 300.f;
	Data->AttackDistance = 600.f;
	Data->InteractionDistance = 800.f;
	
	m_AIState->SetInfo("IggyScorchMonster", Data);
}

void AIS_AICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AIS_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Material Element Count
	int32	ElementCount = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
		m_MtrlArray.Add(GetMesh()->CreateDynamicMaterialInstance(i));


	// ���� ��ٿ��� 3�ʷ� ����
	if (IsValid(m_AttackCooldownComp))
		m_AttackCooldownComp->SetCooldownTime(3.f);

	float RandSize = FMath::FRand();
	// 0.0f���� 0.33f���� ����
	RandSize /= 3.f;
	// �ּһ���� 0.4�迡�� 0.77��� ����
	RandSize += 0.4f;

	// RandSize�� 0.7f���� ū ������ ����Ʈ�� ����
	if (RandSize >= 0.7f)
		m_IsElite = true;

	if (m_IsElite) {
		RandSize = 1.f;

		// HP, ���ݷ� ���� �����͸� ��ȭ.
		m_AIState;


	}

	GetMesh()->SetRelativeScale3D(GetMesh()->GetRelativeScale3D() * RandSize);
}

void AIS_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ��ٿ��� üũ��, ��Ʈ�ѷ��� ������ ���� �������ش�.
	if (IsValid(m_AttackCooldownComp)) {
		if (m_AttackCooldownComp->IsCooldown())
			m_AttackCooldownComp->UpdateCooldown(DeltaTime);
		else {
			// ��ٿ��� �����ٸ�, ��Ʈ�ѷ� �������� ���� ��ٿ��� false�� �ٲ��ش�.
			AIS_AIController* AIController = Cast<AIS_AIController>(GetController());

			if (IsValid(AIController))
				AIController->SetAttackPossibleToBB();
		}
	}


	// Dissolve ó��
	if (m_DissEnable)
	{
		m_DissCurTime += DeltaTime;

		if (m_DissCurTime >= m_DissTime)
			Destroy();

		// ������ ���Ѵ�.
		float	Ratio = m_DissCurTime / m_DissTime;
		Ratio = 1.f - Ratio;
		Ratio = Ratio * 2.f - 1.f;

		for (auto& Mtrl : m_MtrlArray)
			Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
	}
}

float AIS_AICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Damage Widget
	if (IsValid(m_DamageTextWidgetClass))
	{
		UDamageTextWidget* DamageWidget = CreateWidget<UDamageTextWidget>(GetWorld(), m_DamageTextWidgetClass);

		if (IsValid(DamageWidget))
		{
			DamageWidget->AddToViewport();

			DamageWidget->SetDamageText(DamageAmount * 10, GetActorLocation());

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D ScreenPosition;
			PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
			DamageWidget->SetPositionInViewport(ScreenPosition);
		}
	}



	// ���� ó��
	if (m_AIState->Damage(DamageAmount)) {
		// �׾���.
		Cast<UIS_AIAnimInst>(GetMesh()->GetAnimInstance())->SetDeath();

		if(IsValid(m_Widget))
			m_Widget->SetVisibility(false);
	
		//DeathEnd();

		return DamageAmount;
	}



	// HPBar Widget
	float MaxHP = m_AIState->GetHPMax();
	float CurrentHP = m_AIState->GetHP();

	float Value = CurrentHP / MaxHP;

	if (IsValid(m_Widget)) {
		UProgressBar* ProgressBar = Cast<UProgressBar>(m_Widget->GetWidget()->GetWidgetFromName(TEXT("MonsterBar")));

		if(IsValid(ProgressBar))
			ProgressBar->SetPercent(Value);
	}


	Cast<UIS_AIAnimInst>(GetMesh()->GetAnimInstance())->SetHitEnable();

	return DamageAmount;
}

void AIS_AICharacter::ShootFireBomb(FVector TargetLoc)
{
	FVector StartLocation = GetActorLocation(); // ���� ��ġ

	TargetLoc.Z = StartLocation.Z;

	FVector ShootDirection = (TargetLoc - StartLocation).GetSafeNormal();
	FRotator ShootRotation = ShootDirection.Rotation();

	GetWorld()->SpawnActor<AFirebombProjectile>(GetActorLocation(), ShootRotation);

	if (IsValid(m_AttackCooldownComp)) {
		// ���� ��ٿ��� �����Ѵ�.
		m_AttackCooldownComp->StartCooldown();

		// ��Ʈ�ѷ� �������� ���� ��ٿ��� true ���·� �ٲ��ش�.
		AIS_AIController* AIController = Cast<AIS_AIController>(GetController());

		if (IsValid(AIController))
			AIController->SetAttackPossibleToBB(false);
	}
}

void AIS_AICharacter::DeathEnd()
{
	// Dissolve�� Ȱ��ȭ�Ѵ�.
	for (auto& Mtrl : m_MtrlArray) 
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"), 1.f);

	m_DissEnable = true;
}
