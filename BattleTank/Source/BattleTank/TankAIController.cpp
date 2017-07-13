// Copyright VanatisUnreal

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* controlledTank = GetPawn();
	APawn* targetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(controlledTank && targetTank))
	{
		return;
	}

	UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();

	MoveToActor(targetTank, AcceptanceRadius);
	aimingComponent->AimAt(targetTank->GetActorLocation());
	aimingComponent->Fire();
}