// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Engine/DecalActor.h"
#include "Grux_Earthquake_Lava_Decal.generated.h"

UCLASS()
class SACPROJECT_API AGrux_Earthquake_Lava_Decal : public ADecalActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrux_Earthquake_Lava_Decal();

protected:
	TObjectPtr<AActor>		m_DecalOwner;

protected:
	UPROPERTY(Category = "MaxScale", EditAnywhere, BlueprintReadWrite)
	float m_MinScale;

	UPROPERTY(Category = "MaxScale", EditAnywhere, BlueprintReadWrite)
	float m_MaxScale;

	UPROPERTY(Category = "ScaleSpeed", EditAnywhere, BluePrintReadWrite)
	float m_ScaleSpeed;

protected:
	float m_ScaleTime;

public:
	inline void SetDecalOwner(AActor* DecalOwner) { m_DecalOwner = DecalOwner; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
