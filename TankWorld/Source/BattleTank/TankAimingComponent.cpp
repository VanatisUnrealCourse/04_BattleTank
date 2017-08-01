// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankTurret* turret, UTankBarrel* barrel)
{
	Turret = turret;
	Barrel = barrel;
	AimDirection = FVector(1.0f, 0.0f, 0.0f);
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick Ticktype, FActorComponentTickFunction* ThisTickFunction)
{
	if (AmmoRemaining <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector aimLocation)
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
		LaunchSpeed,
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

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		if (!ensure(Barrel))
		{
			return;
		}
		if (!ensure(ProjectileBlueprint))
		{
			return;
		}
		
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		--AmmoRemaining;
	}
}

void UTankAimingComponent::MoveBarrelToAimDirection(FVector aimDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	AimDirection = aimDirection;
	FRotator aimRotator = aimDirection.Rotation();
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);

	//Shortest route
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		Turret->Rotate(deltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-deltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

	FVector barrelForward = Barrel->GetForwardVector();
	return !barrelForward.Equals(AimDirection, 0.1f);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoRemaining() const
{
	return AmmoRemaining;
}