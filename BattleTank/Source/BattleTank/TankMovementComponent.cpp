// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float throwValue)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(throwValue);
}

void UTankMovementComponent::IntendMoveRight(float throwValue)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(-throwValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = moveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	IntendMoveForward(forwardThrow);

	float rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;
	IntendMoveRight(rightThrow);
	UE_LOG(LogTemp, Warning, TEXT("Right: %f  - Forward: %f"), rightThrow, forwardThrow)
}