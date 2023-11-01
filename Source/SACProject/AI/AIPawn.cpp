// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AIState.h"

TObjectPtr<UDataTable> AAIPawn::m_AIDataTable;

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AIState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));
}

void AAIPawn::LoadAIData()
{
	m_AIDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Data/DT_AIData.DT_AIData'"));
}

const FAIDataTable* AAIPawn::FindAIData(const FName& Name)
{
	return m_AIDataTable->FindRow<FAIDataTable>(Name, TEXT(""));
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!IsValid(m_AIDataTable))
	{
		LoadAIData();
	}

	if (IsValid(m_AIDataTable))
	{
		//LOG(TEXT("AIDataTable Valid"));

		const FAIDataTable* Data = FindAIData(m_Name);

		if (Data)
		{
			m_AIState->SetInfo(m_Name.ToString(), Data);

			m_Movement->MaxSpeed = Data->MoveSpeed;
		}
	}
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

