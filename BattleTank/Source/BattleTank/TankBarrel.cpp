// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0, 1.0);
	float elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = RelativeRotation.Pitch + elevationChange;
	newElevation = FMath::Clamp<float>(newElevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(newElevation, 0.0f, 0.0f));
}