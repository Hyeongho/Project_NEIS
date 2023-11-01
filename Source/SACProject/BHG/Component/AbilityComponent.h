// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACPROJECT_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();


protected:
	UPROPERTY(Category = "Abilitys", EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class UDefaultAbility>> m_Abilitys;
	bool	m_Player;

	float m_PlayerForwardSpeed;
	float m_PlayerRightSpeed;

	bool m_MoveOn;
	bool m_MoveLock;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	class UDefaultAbility* FindAbility(const FName& AbilityName);	

public:
	float GetPlayerForwardSpeed();
	float GetPlayerRightSpeed();
	const bool& GetMoveEnable() const { return m_MoveOn; }
	const bool& GetMoveLock() const { return m_MoveLock; }


public:
	void SetPlayer(bool PlayerEnable) { m_Player = PlayerEnable; }
	void SetMoveEnable(bool Enable) { m_MoveOn = Enable; }
	void SetMoveLockEnable(bool Enable) { m_MoveLock = Enable; }

public:
	// Ability 등록
	void GiveAbility(TSubclassOf<UDefaultAbility> Ability);

	// Ability 실행
	void ActivatedAbility(FName AbilityName);

	// Ability 종료
	void EndAbility(FName AbilityName);

	//Ability 후처리 Event
	void ActivatedAbilityEvent(FName EventName, class APawn* Owner, class APawn* Target, int32 Value = 0);

		
};
