// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameModeBase::ActorDied(AActor* deadActor)
{
	if (deadActor == tank)
	{
		tank->HandleDestruction();
		toonTanksPlayerController->SetPlayerEnabledState(false);

		//Lose the game
		GameOver(false);
	}
	else if(ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->HandleDestruction();
		towerCount--;

		if (towerCount == 0)
		{
			//Win the game
			GameOver(true);
		}
	}
}

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameModeBase::HandleGameStart()
{
	//Pick up the amount of towers in the world
	towerCount = GetTargetTowerCount();

	//Get the pawn oh the game
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Get the player controller
	toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	//Start delay
	if (toonTanksPlayerController) 
	{
		toonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle delayTimer;

		FTimerDelegate delayDelegate = FTimerDelegate::CreateUObject(toonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(delayTimer, delayDelegate, startDelay, false);
	} 

}

int32 AToonTanksGameModeBase::GetTargetTowerCount()
{
	TArray<AActor*> towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);

	UE_LOG(LogTemp, Display, TEXT("Tower count: %i"), towers.Num())

	return towers.Num();
}
