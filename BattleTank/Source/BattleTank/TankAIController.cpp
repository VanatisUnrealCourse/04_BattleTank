// Fill out your copyright notice in the Description page of Project Settings.

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
	
	if (targetTank)
	{
		controlledTank->AimAt(targetTank->GetActorLocation());
		controlledTank->Fire();
	}
}