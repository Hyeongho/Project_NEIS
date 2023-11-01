// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultAIAnimInstance.h"
#include "Grux_AIAnimInst.generated.h"


enum class EGruxStampede {
	Stampede_Start,
	Stampede_Run,
	Stampede_Attack,
	Stampede_Stun
};

/**
 * 
 */
UCLASS()
class SACPROJECT_API UGrux_AIAnimInst : public UDefaultAIAnimInstance
{
	GENERATED_BODY()
	
public:
	UGrux_AIAnimInst();

protected:
	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AGrux_AICharacter>	m_GruxCharacter;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_AttackMontage;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> m_Skill1_DoublePain_Montage;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> m_Skill2_Stampede_Montage;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> m_Skill3_Eearthquake_Montage;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	UPROPERTY(Category = "Variable", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool m_IsStun;

private:
	int32 m_AttackIndex;
	bool m_AttackEnable;

protected:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

public:
	inline EAIAnimType GetAnimType() const;
	void SetDeath() { m_AnimType = EAIAnimType::Death; }
	void SetStun();			
	void SetStunRelease();

public:
	void Attack_Anim();
	void Skill1_DoublePain_Anim();
	void Skill2_StampedeReady_Anim();
	void Skill2_StampedeRun_Anim();
	void Skill2_StampedeAttack_Anim();
	void Skill2_StampedeStun_Anim();
	void Skill3_Earthquake_Anim();



private: // Notify
	UFUNCTION()
	void AnimNotify_StartEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_Attack1End();

	UFUNCTION()
	void AnimNotify_Attack2End();

	UFUNCTION()
	void AnimNotify_Attack3End();

	UFUNCTION()
	void AnimNotify_Attack4End();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DoublePain_Attack();

	UFUNCTION()
	void AnimNotify_DoublePain_End();

	UFUNCTION()
	void AnimNotify_ReadyEnd();

	UFUNCTION()
	void AnimNotify_Stampede_Attack();

	UFUNCTION()
	void AnimNotify_Stampede_End();

	UFUNCTION()
	void AnimNotify_Earthquake();

	UFUNCTION()
	void AnimNotify_Earthquake_End();

};
