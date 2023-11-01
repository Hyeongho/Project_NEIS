// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "../Effect/BaseEffect.h"
#include "ProjectileBase.generated.h"

UCLASS()
class SACPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	UPROPERTY(Category = "ProjectileBody", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent>		m_Box;

	UPROPERTY(Category = "ProjectileMesh", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent>	m_Mesh;

	UPROPERTY(Category = "ProjectileMovement", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent>	m_Move;

	UPROPERTY(Category = "ProjectieSpeed", EditAnywhere, BlueprintReadWrite)
	float					m_ProjectieSpeed;

	UPROPERTY(Category = "ProjectileEffect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseEffect>	m_ProjectileEffect;

	UPROPERTY(Category = "DamageMin", EditAnywhere, BlueprintReadWrite)
	int32	m_MinDamage;

	UPROPERTY(Category = "DamageMax", EditAnywhere, BlueprintReadWrite)
	int32	m_MaxDamage;

protected:
	TObjectPtr<ACharacter>	m_Shooter;
	TObjectPtr<ACharacter>	m_Target;

	int32	m_TrueDamage;

	float		m_Length;


public:
	class ACharacter* GetTargetActor() const { return m_Target; }
	class ACharacter* GetShooterActor() const { return m_Shooter; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	virtual void ProjectileFire(FVector Velocity, class ACharacter* Shooter);

protected:
	UFUNCTION()
		virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
