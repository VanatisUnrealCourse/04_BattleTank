// Copyright VanatisUnreal

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// How close can the AITank get to the target before stopping
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 1000;
};
