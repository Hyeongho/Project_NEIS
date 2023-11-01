// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAICharacter.h"

ADefaultAICharacter::ADefaultAICharacter()
	: Super()
{

}

void ADefaultAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ADefaultAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADefaultAICharacter::OnDamaged(int32 Damage, ACharacter* Shooter, ACharacter* Target, bool Counter)
{
}

float ADefaultAICharacter::GetCapusuleHalfHeight()
{
	return GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}
