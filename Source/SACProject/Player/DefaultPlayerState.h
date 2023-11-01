// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_AttackPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_ArmorPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_HP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_HPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_MP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_MPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_AttackDistance;

public:
	FORCEINLINE int32 GetAttackPoint() const { return m_AttackPoint; }
	FORCEINLINE int32 GetArmorPoint() const { return m_ArmorPoint; }
	FORCEINLINE int32 GetHP() const { return m_HP; }
	FORCEINLINE int32 GetHPMax() const { return m_HPMax; }
	FORCEINLINE int32 GetMP() const { return m_MP; }
	FORCEINLINE int32 GetMPMax() const { return m_MPMax; }
	FORCEINLINE float GetMoveSpeed() const { return m_MoveSpeed; }
	FORCEINLINE float GetAttackDistance() const { return m_AttackDistance; }

public:
	bool AddHP(int32 HP);
	bool AddMP(int32 MP);

public:
	void SetPlayerData(int32 AttackPoint, int32 ArmorPoint, int32 HP, int32 MP, float MoveSpeed, float AttackDistance);
	void InitPlayerData(FName TableName);
};
