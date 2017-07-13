// Copyright VanatisUnreal

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
* Responsible for helping the player control the tank. This includes aiming and moving.
*/
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimingComponent);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

private:
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXPosition = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYPosition = 0.3333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 10000;
};
