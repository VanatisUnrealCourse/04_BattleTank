// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	FVector appliedForce = GetForwardVector() * throttle * TrackMaxDrivingForce;
	FVector appliedLocation = GetComponentLocation();
	
	// UPrimitiveComponent is the most abstract class that allows the adding of forces
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(appliedForce, appliedLocation);
}


