// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "PortalObject.generated.h"

UCLASS()
class SACPROJECT_API APortalObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalObject();

protected:
	UPROPERTY(Category = "Box", EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UBoxComponent>		m_PortalBox;

	UPROPERTY(Category = "PortalEffect", EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UParticleSystemComponent>	m_PortalEffect;

	UPROPERTY(Category = "NextLevelName", EditAnywhere, BlueprintReadWrite)
		FName			m_LevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void PortalBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
