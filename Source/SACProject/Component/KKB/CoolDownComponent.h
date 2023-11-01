// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "CoolDownComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SACPROJECT_API UCoolDownComponent : public UObject
{
	GENERATED_BODY()

public:
    UCoolDownComponent();

private:
    // ��ٿ� �ð�
    UPROPERTY(Transient)
    float m_CooldownTime;

    // ��ٿ� �ܿ� �ð�
    UPROPERTY(Transient)    
    float m_TimeRemaining;

public:
    // ��ٿ� �ð��� ����.
    void SetCooldownTime(float CooldownTime) { m_CooldownTime = CooldownTime; }

public:
    // ��ٿ� ���θ� ��ȯ.
    UFUNCTION(BlueprintCallable)
    bool IsCooldown() const;

    // ��ٿ� �ܿ� �ð��� ��ȯ.
    UFUNCTION(BlueprintCallable)
    inline float RemainTime() const { return m_TimeRemaining; }


    // ��ٿ� ����
    UFUNCTION(BlueprintCallable)
    void ResetCooldown();

    // ��ٿ� ī��Ʈ ����
    UFUNCTION(BlueprintCallable)
    void StartCooldown();

    // ��ٿ��� ������Ʈ. �ش� �Լ��� Tick ��� ���������� ������Ʈ����� ��.
    UFUNCTION(BlueprintCallable)
    float UpdateCooldown(float DeltaTime);
	
};
