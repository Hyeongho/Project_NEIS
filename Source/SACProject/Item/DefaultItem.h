// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DefaultItem.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USphereComponent;

UCLASS()
class SACPROJECT_API ADefaultItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/* 아이템 Mesh */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> m_ItemMesh;

	/* 아이템의 BoxComponent */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> m_CollisionBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Property", meta = (AllowPrivateAccess = true))
	FString m_ItemName;

/* Getter */
public:
	FORCEINLINE UStaticMeshComponent* GetItemMesh() const { return m_ItemMesh; }
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return m_CollisionBox; }
	FORCEINLINE const FString& GetItemName() const { return m_ItemName; }

};
