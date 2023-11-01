// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "../DefaultGameInstance.h"

bool ADefaultPlayerState::AddHP(int32 HP)
{
	m_HP += HP;

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

bool ADefaultPlayerState::AddMP(int32 MP)
{
	m_MP += MP;

	if (m_MP <= 0)
	{
		m_MP = 0;
		return true;
	}

	else if (m_MP > m_MPMax)
	{
		m_MP = m_MPMax;
	}

	return false;
}

void ADefaultPlayerState::SetPlayerData(int32 AttackPoint, int32 ArmorPoint, int32 HP, int32 MP, float MoveSpeed, float AttackDistance)
{
	m_AttackPoint = AttackPoint;
	m_ArmorPoint = ArmorPoint;
	m_HP = HP;
	m_HPMax = HP;
	m_MP = MP;
	m_MoveSpeed = MoveSpeed;
	m_AttackDistance = AttackDistance;
}

void ADefaultPlayerState::InitPlayerData(FName TableName)
{
	auto GameInst = GetWorld()->GetGameInstance<UDefaultGameInstance>();

	const FPlayerDataTable* Data = GameInst->FindPlayerData(TableName);

	if (Data)
	{
		m_AttackPoint = Data->AttackPoint;
		m_ArmorPoint = Data->ArmorPoint;
		m_HP = Data->HP;
		m_HPMax = Data->HP;
		m_MP = Data->MP;
		m_MPMax = Data->MP;
		m_MoveSpeed = Data->MoveSpeed;
		m_AttackDistance = Data->AttackDistance;
	}
}
