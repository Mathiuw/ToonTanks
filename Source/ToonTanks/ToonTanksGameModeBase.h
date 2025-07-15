// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* deadActor);

protected:

	virtual void BeginPlay()override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	float startDelay = 4.f;

	class ATank* tank;
	class AToonTanksPlayerController* toonTanksPlayerController;

	void HandleGameStart();

	int32 towerCount = 0;

	int32 GetTargetTowerCount();
};
