// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialise(UTankTurret* turret, UTankBarrel* barrel)
{
	Turret = turret;
	Barrel = barrel;
}

void UTankAimingComponent::AimAt(FVector aimLocation, float launchSpeed)
{
	if (!ensure(Barrel))
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
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	FRotator aimRotator = aimDirection.Rotation();
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}