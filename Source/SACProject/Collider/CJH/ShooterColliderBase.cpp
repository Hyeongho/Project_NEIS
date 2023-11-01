// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterColliderBase.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "../../AI/CJH/ShooterMonster.h"
#include "../../UI/CJH/DamageTextWidget.h"

// Sets default values
AShooterColliderBase::AShooterColliderBase()
	: Super()
	, m_Damage(10)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	m_HitBox->SetCollisionProfileName("PlayerAttackOverlap");
	m_HitBox->SetBoxExtent(FVector(500.0, 500.0, 150.0));

	m_HitBox->SetGenerateOverlapEvents(true);
	m_HitBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HitBoxBeginOverlap);
	m_HitBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::HitBoxEndOverlap);
	SetRootComponent(m_HitBox);

}

// Called when the game starts or when spawned
void AShooterColliderBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(0.5f);
}

void AShooterColliderBase::HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어가 맞았을 경우
	AShooterCharacter* Shooter = Cast<AShooterCharacter>(OtherActor);
	if (IsValid(Shooter))
	{
		// Owner는 몬스터로 설정되어 있음
		if (AShooterMonster* Monster = Cast<AShooterMonster>(GetOwner()))
		{
			UGameplayStatics::ApplyDamage(Shooter, m_Damage, Monster->GetController(), Monster, UDamageType::StaticClass());
		}
	}

	// 몬스터가 맞았을 경우
	AShooterMonster* Monster = Cast<AShooterMonster>(OtherActor);
	if (IsValid(Monster))
	{
		int32 RandomDamage = FMath::RandRange(-5, 5);
		UGameplayStatics::ApplyDamage(Monster, m_Damage + RandomDamage, GetWorld()->GetFirstPlayerController(), GetOwner(), UDamageType::StaticClass());

		if (IsValid(m_DamageTextWidgetClass))
		{
			UDamageTextWidget* DamageWidget = CreateWidget<UDamageTextWidget>(GetWorld(), m_DamageTextWidgetClass);
			if (IsValid(DamageWidget))
			{
				DamageWidget->AddToViewport();
				DamageWidget->SetDamageText(m_Damage + RandomDamage, Monster->GetActorLocation());



				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				FVector2D ScreenPosition;
				PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
				DamageWidget->SetPositionInViewport(ScreenPosition);
			}
		}
	}
}

void AShooterColliderBase::HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AShooterColliderBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterColliderBase::SetOwnerCharacter(ACharacter* InCharacter)
{
	m_OwnerCharacter = InCharacter;
}

