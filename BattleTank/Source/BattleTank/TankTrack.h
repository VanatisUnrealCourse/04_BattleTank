// Copyright VanatisUnreal

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
* TankTrack is used to set maximum driving force and to apply forces to the tank.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1.0f and 1.0f
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	void DriveTrack();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit);
	
	UTankTrack();
	virtual void BeginPlay() override;
	void ApplySidewaysForce();

private:
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000.0f; // Assume 40 ton tank at 1g acceleration

	float CurrentThrottle = 0.0f;
};
