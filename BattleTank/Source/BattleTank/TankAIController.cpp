// Copyright VanatisUnreal

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* targetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (ensure(targetTank))
	{
		MoveToActor(targetTank, AcceptanceRadius);

		controlledTank->AimAt(targetTank->GetActorLocation());
		controlledTank->Fire();
	}
}