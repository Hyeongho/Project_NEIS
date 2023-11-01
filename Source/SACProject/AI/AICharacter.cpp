// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "AIState.h"

TObjectPtr<UDataTable> AAICharacter::m_AIDataTable;

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AIState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAICharacter::LoadAIData()
{
	m_AIDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Data/DT_AIData.DT_AIData'"));
}

const FAIDataTable* AAICharacter::FindAIData(const FName& Name)
{
	return m_AIDataTable->FindRow<FAIDataTable>(Name, TEXT(""));
}

void AAICharacter::OnConstruction(const FTransform& Transform)
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

			GetCharacterMovement()->MaxWalkSpeed = Data->MoveSpeed;
		}
	}
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

