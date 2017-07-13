// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0, 1.0);
	float rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0.0f, newRotation, 0.0f));
}

