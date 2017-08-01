// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	FVector appliedForce = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector appliedLocation = GetComponentLocation();

	// UPrimitiveComponent is the most abstract class that allows the adding of forces
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(appliedForce, appliedLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce()
{
	//Calculate the required accelration to correct sideways slipping
	float deltaTime = GetWorld()->GetDeltaSeconds();
	float slipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector correctionAcceleration = -slipSpeed / deltaTime * GetRightVector();

	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2; //Two Tracks

	tankRoot->AddForce(correctionForce);
}