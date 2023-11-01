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
    ProjectileMovementComponent->InitialSpeed = 3000.0f; // 초기 발사 속도 설정
    ProjectileMovementComponent->MaxSpeed = 3000.0f; // 최대 속도 설정
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true; // 장애물과 충돌 시 반사 여부
    ProjectileMovementComponent->Bounciness = 0.3f; // 반사 계수
}

// Called when the game starts or when spawned
void ATestProjectile::BeginPlay()
{
    Super::BeginPlay();


    // 목표 위치
    FVector TargetLocation = FVector(1750.f, 1650.f, 0.0f);

    // 현재 위치
    FVector StartLocation = GetActorLocation();

    // 중간 위치 (최고 지점 높이 3000.0에 도달)
    FVector Midpoint = (StartLocation + TargetLocation) / 2;
    Midpoint.Z = 3000.0f;

    // 중간 지점에서 목표 위치로 향하는 방향 벡터 계산
    FVector TargetDirection = (TargetLocation - Midpoint).GetSafeNormal();

    // 프로젝타일을 중간 지점으로 발사
    ProjectileMovementComponent->Velocity = TargetDirection * ProjectileMovementComponent->InitialSpeed;

    // 프로젝타일의 수명을 설정하고 시간이 지난 후 자동으로 제거될 수 있도록 합니다.
    SetLifeSpan(5.0f);
	
}

// Called every frame
void ATestProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
