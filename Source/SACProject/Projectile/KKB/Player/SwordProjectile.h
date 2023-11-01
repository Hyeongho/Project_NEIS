// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Meson_Projectile.h"
#include "SwordProjectile.generated.h"

UCLASS()
class SACPROJECT_API ASwordProjectile : public AMeson_Projectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordProjectile();

protected:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> m_SwordProj;


public:
	void Shoot(float Size);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnComponentHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
