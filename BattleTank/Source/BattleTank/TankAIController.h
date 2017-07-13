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

protected:
	// How close can the AITank get to the target before stopping
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 800;
};
