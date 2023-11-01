// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterLauncher.h"
#include "../../Player/CJH/ShooterCharacter.h"
#include "../../Projectile/CJH/ShooterProjectileBase.h"

AShooterLauncher::AShooterLauncher()
	: Super()
{
}

void AShooterLauncher::SendBullet()
{
	// ��ź�� �� �� �ֵ���
	const USkeletalMeshSocket* Muzzle = GetWeaponMesh()->GetSocketByName(TEXT("Muzzle"));
	if (Muzzle)
	{
		const FTransform MuzzleSocketTrans = Muzzle->GetSocketTransform(GetWeaponMesh());

		if (m_MuzzleFlashParticle)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MuzzleFlashParticle, MuzzleSocketTrans);

		FVector BeamEndLocation;
		FHitResult CrosshairHitResult;
		GetOwnerCharacter()->TraceUnderCrosshairs(CrosshairHitResult, BeamEndLocation);

		// �� ������
		const FRotator ShotDir = (BeamEndLocation - MuzzleSocketTrans.GetLocation()).Rotation();

		// ��ź ����
		if (IsValid(m_GrenadeProjectileClass))
			GetWorld()->SpawnActor<AShooterProjectileBase>(m_GrenadeProjectileClass, MuzzleSocketTrans.GetLocation(), ShotDir);
	}
}
