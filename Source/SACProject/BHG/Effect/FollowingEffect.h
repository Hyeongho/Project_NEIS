// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseEffect.h"
#include "FollowingEffect.generated.h"

/**
 * 
 */
UCLASS()
class SACPROJECT_API AFollowingEffect : public ABaseEffect
{
	GENERATED_BODY()

public:
	AFollowingEffect();

protected:
	UPROPERTY(Category = "FollowSocket", EditAnywhere, BlueprintReadWrite)
	bool	m_FollowSocket;

	UPROPERTY(Category = "SocketName", EditAnywhere, BlueprintReadWrite)
	FName	m_SocketName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
