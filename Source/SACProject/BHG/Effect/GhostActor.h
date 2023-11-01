// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "GhostActor.generated.h"

UCLASS()
class SACPROJECT_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostActor();

protected:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UPoseableMeshComponent>	m_PoseableComp;

	UPROPERTY(Category = "Opacity", EditAnywhere, BlueprintReadWrite)
	float OpacityTime;

	UPROPERTY(Category = "Color", EditAnywhere, BlueprintReadWrite)
	FVector	mColor;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CopyAnimation(USkeletalMeshComponent* CopyComp);
	void SetGhostColor(FVector GhostColor);

};
