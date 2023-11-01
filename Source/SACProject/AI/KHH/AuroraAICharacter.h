// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AICharacter.h"
#include "AuroraAICharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAICharacterState : uint8
{
	Alive,
	Death
};

USTRUCT(BlueprintType)
struct FAuroraSkillCoolTime
{
	GENERATED_BODY()

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurCooltime;

	UPROPERTY(Category = "Data", EditAnywhere, meta = (AllowPrivateAccess = true))
	float MaxCooltime;

	bool IsCool;
};

UCLASS()
class SACPROJECT_API AAuroraAICharacter : public AAICharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AAuroraAICharacter();

protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAICharacterState m_State;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<struct FAuroraSkill> m_Skill;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FAuroraSkillCoolTime> m_SkillCoolTime;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> m_DashAttack;

private:
	bool m_StartEnd;

	bool m_IsDass;

	bool m_AttackEnd;

private: // Dissolve
	TArray<TObjectPtr<UMaterialInstanceDynamic>> m_MtrlArray;
	bool m_DissEnable;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_DissTime;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_DissCurTime;

	TObjectPtr<class UFrozenCaveWidget> m_FrozenCaveWidget;

protected:
	//virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 생성한 객체가 제거될때 호출된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetStartEnd(bool StartEnd)
	{
		m_StartEnd = StartEnd;
	}

	bool GetStartEnd() const
	{
		return m_StartEnd;
	}

	void SetDass(bool Dass)
	{
		m_IsDass = Dass;
	}

	float GetHalfHeight() const
	{
		return GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius() const
	{
		return GetCapsuleComponent()->GetScaledCapsuleRadius();
	}

	bool IsDeath()
	{
		if (m_State == EAICharacterState::Alive)
		{
			return false;
		}

		return true;
	}

	TArray<FAuroraSkillCoolTime> GetSkillCoolTimeArray() const
	{
		return m_SkillCoolTime;
	}

	void UseSkill(int Index)
	{
		m_SkillCoolTime[Index].IsCool = true;
	}

	bool GetIsCool(int Index) const
	{
		return m_SkillCoolTime[Index].IsCool;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		m_AttackEnd = AttackEnd;
	}

	bool GetAttackEnd() const
	{
		return m_AttackEnd;
	}

	void SetCollisionEnable()
	{
		if (m_DashAttack->GetCollisionEnabled() == ECollisionEnabled::QueryOnly)
		{
			m_DashAttack->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		else if (m_DashAttack->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
		{
			m_DashAttack->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}

	void SetAttackIndex(int Index);

	void SetSkillCoolTime(float CoolTime, float MaxCoolTime, bool IsCool);

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void Attack();

	void PlaySkill(int Index);

	void Death();

	void Freeze();

	UFUNCTION()
	void Dash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Ultimate();
};
