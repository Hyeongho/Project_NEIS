// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Meson_BaseCol.generated.h"

UCLASS()
class SACPROJECT_API AMeson_BaseCol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeson_BaseCol();

protected:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent>		m_DefaultHitBox;

	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UParticleSystemComponent>	m_HitEffect;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_Damage;

	TObjectPtr<AActor>	m_ColOwner;

public:
	void SetDamage(int32 Damage) { m_Damage = Damage; }
	void SetColOwner(AActor* Actor) { m_ColOwner = Actor; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
