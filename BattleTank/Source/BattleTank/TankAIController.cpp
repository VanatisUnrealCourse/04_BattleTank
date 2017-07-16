// Copyright VanatisUnreal

#include "BattleTank.h"
#include "Tank.h"
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
	if (aimingComponent->GetFiringState() == EFiringState::Locked)
	{
		aimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* inPawn)
{
	Super::SetPawn(inPawn);

	if (inPawn)
	{
		ATank* possessedTank = Cast<ATank>(inPawn); 
		if (!ensure(possessedTank))
		{
			return;
		}

		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn()))
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}