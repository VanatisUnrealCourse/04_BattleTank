// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	if (!barrelToSet)
	{
		return;
	}

	Barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	if (!turretToSet)
	{
		return;
	}
	Turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector aimLocation, float launchSpeed)
{
	if (!Barrel)
	{
		return;
	}


	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		aimLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bAimSolution)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelToAimDirection(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelToAimDirection(FVector aimDirection)
{
	FRotator aimRotator = aimDirection.Rotation();
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}