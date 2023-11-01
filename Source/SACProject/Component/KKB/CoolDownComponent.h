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
    // 쿨다운 시간
    UPROPERTY(Transient)
    float m_CooldownTime;

    // 쿨다운 잔여 시간
    UPROPERTY(Transient)    
    float m_TimeRemaining;

public:
    // 쿨다운 시간을 지정.
    void SetCooldownTime(float CooldownTime) { m_CooldownTime = CooldownTime; }

public:
    // 쿨다운 여부를 반환.
    UFUNCTION(BlueprintCallable)
    bool IsCooldown() const;

    // 쿨다운 잔여 시간을 반환.
    UFUNCTION(BlueprintCallable)
    inline float RemainTime() const { return m_TimeRemaining; }


    // 쿨다운 리셋
    UFUNCTION(BlueprintCallable)
    void ResetCooldown();

    // 쿨다운 카운트 시작
    UFUNCTION(BlueprintCallable)
    void StartCooldown();

    // 쿨다운을 업데이트. 해당 함수를 Tick 등에서 지속적으로 업데이트해줘야 함.
    UFUNCTION(BlueprintCallable)
    float UpdateCooldown(float DeltaTime);
	
};
