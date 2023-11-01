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
			// �ϴ� �� ����Ʈ�� ����
			FVector ShotPoint = BeamEndLocation;

			// �� ������
			FVector ShotDir = BeamEndLocation - MuzzleSocketTrans.GetLocation();
			ShotDir.Normalize();
			FRotator ShotRotation = UKismetMathLibrary::MakeRotFromX(UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ShotDir, 5.0f));

			// �� ���� ������ Muzzle
			const FVector FireStart = MuzzleSocketTrans.GetLocation();
			//const FVector StartToEnd = OutBeamLocation - MuzzleSocketLocation;
			
			// �� �� ������ ������������ �������� ���� �������� �����Ÿ���ŭ
			const FVector FireEnd = FireStart + ShotRotation.Vector() * m_WeaponFireRange;

			// �� ����Ʈ ����
			ShotPoint = FireEnd;

			FCollisionQueryParams Param;
			Param.AddIgnoredActor(this);
			Param.AddIgnoredActor(GetOwnerCharacter());

			FHitResult FireHitResult;
			GetWorld()->LineTraceSingleByChannel(FireHitResult, FireStart, FireEnd, ECollisionChannel::ECC_Visibility, Param);
			if (FireHitResult.bBlockingHit)
			{
				// ���� ������ ������ �� ����Ʈ ����
				ShotPoint = FireHitResult.Location;

				if (IsValid(FireHitResult.GetActor()))
				{
					// ���� bullethit �������̽��� ��ӹ��� actor�� ����ٸ�
					IBulletHit* BulletHitInterface = Cast<IBulletHit>(FireHitResult.GetActor());
					if (BulletHitInterface)
						BulletHitInterface->BulletHit_Implementation(FireHitResult);
					else
					{
						if (m_ImpactParticle)
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_ImpactParticle, ShotPoint);
					}

					// ������ ó��
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