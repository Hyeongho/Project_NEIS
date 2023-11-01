// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterShotgun.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../AI/CJH/BulletHit.h"
#include "../../AI/CJH/ShooterMonster.h"

AShooterShotgun::AShooterShotgun()
	: Super()
{
}

void AShooterShotgun::SendBullet()
{
	const USkeletalMeshSocket* Muzzle = GetWeaponMesh()->GetSocketByName(TEXT("Muzzle"));
	if (Muzzle)
	{
		const FTransform MuzzleSocketTrans = Muzzle->GetSocketTransform(GetWeaponMesh());

		if (m_MuzzleFlashParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MuzzleFlashParticle, MuzzleSocketTrans);

		TArray<FVector> ImpactPoints;


		FVector BeamEndLocation;
		FHitResult CrosshairHitResult;
		GetOwnerCharacter()->TraceUnderCrosshairs(CrosshairHitResult, BeamEndLocation);
		for (int32 i = 0; i < 9; ++i)
		{
			// 일단 샷 포인트를 지정
			FVector ShotPoint = BeamEndLocation;

			// 샷 방향계산
			FVector ShotDir = BeamEndLocation - MuzzleSocketTrans.GetLocation();
			ShotDir.Normalize();
			FRotator ShotRotation = UKismetMathLibrary::MakeRotFromX(UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ShotDir, 5.0f));

			// 샷 시작 지점은 Muzzle
			const FVector FireStart = MuzzleSocketTrans.GetLocation();
			//const FVector StartToEnd = OutBeamLocation - MuzzleSocketLocation;
			
			// 샷 끝 지점은 시작지점에서 랜덤으로 계산된 방향으로 사정거리만큼
			const FVector FireEnd = FireStart + ShotRotation.Vector() * m_WeaponFireRange;

			// 샷 포인트 갱신
			ShotPoint = FireEnd;

			FCollisionQueryParams Param;
			Param.AddIgnoredActor(this);
			Param.AddIgnoredActor(GetOwnerCharacter());

			FHitResult FireHitResult;
			GetWorld()->LineTraceSingleByChannel(FireHitResult, FireStart, FireEnd, ECollisionChannel::ECC_Visibility, Param);
			if (FireHitResult.bBlockingHit)
			{
				// 만약 맞은게 있으면 샷 포인트 갱신
				ShotPoint = FireHitResult.Location;

				if (IsValid(FireHitResult.GetActor()))
				{
					// 만약 bullethit 인터페이스를 상속받은 actor를 맞췄다면
					IBulletHit* BulletHitInterface = Cast<IBulletHit>(FireHitResult.GetActor());
					if (BulletHitInterface)
						BulletHitInterface->BulletHit_Implementation(FireHitResult);
					else
					{
						if (m_ImpactParticle)
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ImpactParticle, ShotPoint);
					}

					// 데미지 처리
					AShooterMonster* Monster = Cast<AShooterMonster>(FireHitResult.GetActor());
					if (IsValid(Monster))
					{
						int32 RandomDamage = FMath::RandRange(-5, 5);
						UGameplayStatics::ApplyDamage(Monster, GetWeaponDamage() + RandomDamage, GetOwnerCharacter()->GetController(), GetOwnerCharacter(), UDamageType::StaticClass());
						Monster->ShowDamageText(GetWeaponDamage() + RandomDamage, FireHitResult.Location);
					}
				}
			}

			ImpactPoints.Add(ShotPoint);
		}


		if (IsValid(m_BeamParticleSystem))
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_BeamParticleSystem, MuzzleSocketTrans.GetLocation());

			NiagaraComp->SetNiagaraVariableBool(TEXT("User.Trigger"), true);
			NiagaraComp->SetNiagaraVariableVec3(TEXT("User.MuzzlePosition"), MuzzleSocketTrans.GetLocation());

			UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(NiagaraComp, TEXT("User.ImpactPositions"), ImpactPoints);
		}
	}
}