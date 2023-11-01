// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjectile.h"

// Sets default values
ATestProjectile::ATestProjectile()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create a static mesh component for the projectile
    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
    RootComponent = ProjectileMeshComponent;
    ProjectileMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/KKB/CustomMesh/CustomSphere.CustomSphere'"));

    if (MeshAsset.Succeeded()) {
        ProjectileMeshComponent->SetStaticMesh(MeshAsset.Object);
    }


    // Create a projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
    ProjectileMovementComponent->InitialSpeed = 3000.0f; // �ʱ� �߻� �ӵ� ����
    ProjectileMovementComponent->MaxSpeed = 3000.0f; // �ִ� �ӵ� ����
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true; // ��ֹ��� �浹 �� �ݻ� ����
    ProjectileMovementComponent->Bounciness = 0.3f; // �ݻ� ���
}

// Called when the game starts or when spawned
void ATestProjectile::BeginPlay()
{
    Super::BeginPlay();


    // ��ǥ ��ġ
    FVector TargetLocation = FVector(1750.f, 1650.f, 0.0f);

    // ���� ��ġ
    FVector StartLocation = GetActorLocation();

    // �߰� ��ġ (�ְ� ���� ���� 3000.0�� ����)
    FVector Midpoint = (StartLocation + TargetLocation) / 2;
    Midpoint.Z = 3000.0f;

    // �߰� �������� ��ǥ ��ġ�� ���ϴ� ���� ���� ���
    FVector TargetDirection = (TargetLocation - Midpoint).GetSafeNormal();

    // ������Ÿ���� �߰� �������� �߻�
    ProjectileMovementComponent->Velocity = TargetDirection * ProjectileMovementComponent->InitialSpeed;

    // ������Ÿ���� ������ �����ϰ� �ð��� ���� �� �ڵ����� ���ŵ� �� �ֵ��� �մϴ�.
    SetLifeSpan(5.0f);
	
}

// Called every frame
void ATestProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
