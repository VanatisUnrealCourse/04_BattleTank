// Copyright VanatisUnreal

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float damageAmount, struct FDamageEvent const& damageEvent, class AController* eventInstigator, AActor* damageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(damageAmount);
	damagePoints = FMath::Clamp(damagePoints, 0, CurrentHealth);

	CurrentHealth -= damagePoints;
	if (CurrentHealth <= 0)
	{
		//Tank died - do stuff
	}

	return damagePoints;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}