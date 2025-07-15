// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime)override;

	void HandleDestruction();

protected:

	virtual void BeginPlay()override;

private:

	class ATank* tank;

	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	float fireRange;
	
	UPROPERTY(EditAnywhere, Category = "Shoot")
	float firerate = 2.f;

	FTimerHandle fireRateTimerHandle;

	void CheckFireCondition();

	bool CheckTankIsInRange();

};
