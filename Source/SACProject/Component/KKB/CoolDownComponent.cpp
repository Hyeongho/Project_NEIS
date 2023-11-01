// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolDownComponent.h"

UCoolDownComponent::UCoolDownComponent() :
	m_CooldownTime(10.f),
	m_TimeRemaining(0.f)
{
}

bool UCoolDownComponent::IsCooldown() const
{
	return m_TimeRemaining > 0.0f;
}

void UCoolDownComponent::ResetCooldown()
{
    m_TimeRemaining = 0.0f;
}

void UCoolDownComponent::StartCooldown()
{
    m_TimeRemaining = m_CooldownTime;
}

float UCoolDownComponent::UpdateCooldown(float DeltaTime)
{
    if (m_TimeRemaining > 0.0f)
    {
        m_TimeRemaining -= DeltaTime;

        if (m_TimeRemaining < 0.0f)
            m_TimeRemaining = 0.0f;
    }

    return m_TimeRemaining;
}
