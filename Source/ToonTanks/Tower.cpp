// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();

	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::CheckFireCondition, firerate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckTankIsInRange())
	{
		//Rotate the turret
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (CheckTankIsInRange() && tank && tank->bAlive)
	{
		Fire();
	}
}

//Return TRUE if tank is in fire range
bool ATower::CheckTankIsInRange()
{
	if (tank)
	{
		//Get the distance to the tank pawn
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());

		//Checks if tank its within range
		if (distance <= fireRange)
		{
			return true;
		}
	}

	return false;
}
