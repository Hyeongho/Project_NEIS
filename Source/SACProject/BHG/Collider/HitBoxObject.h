// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../Effect/BaseEffect.h"
#include "GameFramework/Actor.h"
#include "HitBoxObject.generated.h"

UCLASS()
class SACPROJECT_API AHitBoxObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBoxObject();

protected:
	UPROPERTY(Category = "HitBox", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent>		m_DefaultHitBox;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseEffect>	m_Effect;

	UPROPERTY(Category = "CounterAttack", EditAnywhere, BlueprintReadWrite)
	bool		m_Counter;

	UPROPERTY(Category = "DamageMin", EditAnywhere, BlueprintReadWrite)
	int32	m_MinDamage;

	UPROPERTY(Category = "DamageMax", EditAnywhere, BlueprintReadWrite)
	int32	m_MaxDamage;

protected:
	int32	m_TrueDamage;

	
protected:
	TObjectPtr<ACharacter>	m_Shooter;
	TObjectPtr<ACharacter>	m_Target;

public:
	class ACharacter* GetTargetActor() const { return m_Target; }
	class ACharacter* GetShooterActor() const { return m_Shooter; }

public:
	void SetCollisionProfile(const FName& ProfileName);
	void SetShooter(ACharacter* Shooter);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void HitBoxDestroy();

protected:
	UFUNCTION()
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);




};
