// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
* TankBarrel is used to move the barrel to the wanted aim elevation.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly)
		float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly)
		float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditDefaultsOnly)
		float MinElevationDegrees = 0.0f;
};
