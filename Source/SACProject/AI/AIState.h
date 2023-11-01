// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACPROJECT_API UAIState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIState();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_InteractionDistance;

public:
	int32 GetAttackPoint()	const
	{
		return m_AttackPoint;
	}

	float GetAttackDistance()
	{
		return m_AttackDistance;
	}

	float GetInteractionDistance()
	{
		return m_InteractionDistance;
	}

public:
	void SetInfo(const FString& Name, const FAIDataTable* Data)
	{
		m_Name = Name;

		m_AttackPoint = Data->AttackPoint;
		m_ArmorPoint = Data->ArmorPoint;
		m_HP = Data->HP;
		m_HPMax = Data->HP;
		m_MP = Data->MP;
		m_MPMax = Data->MP;
		m_MoveSpeed = Data->MoveSpeed;
		m_AttackDistance = Data->AttackDistance;
		m_InteractionDistance = Data->InteractionDistance;
	}

	bool Damage(int32 Dmg)
	{
		m_HP -= Dmg;

		if (m_HP <= 0)
		{
			m_HP = 0;
			return true;
		}

		else if (m_HP > m_HPMax)
		{
			m_HP = m_HPMax;
		}

		return false;
	}

	void SetDamage(float Damage)
	{
		m_HP -= Damage;
	}

	inline int32 GetHP() const
	{
		return m_HP;
	}

public:
	void SetDeath() { Damage(m_HP); }

public:
	inline bool IsHalfHP() const { return m_HPMax / 2 >= m_HP; }
	inline int32 GetHPMax() const { return m_HPMax; }
	inline int32 GetATKPoint() const { return m_AttackPoint; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
