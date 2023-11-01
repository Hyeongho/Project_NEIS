// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ShooterColliderBase.generated.h"

class UBoxComponent;
class UDamageTextWidget;

UCLASS()
class SACPROJECT_API AShooterColliderBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShooterColliderBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HitBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> m_HitBox;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	int32 m_Damage;

	TObjectPtr<ACharacter> m_OwnerCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextWidget> m_DamageTextWidgetClass;

public:
	FORCEINLINE ACharacter* GetOwnerCharacter() const { return m_OwnerCharacter; }

public:
	void SetOwnerCharacter(ACharacter* InCharacter);
};
