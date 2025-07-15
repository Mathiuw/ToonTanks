// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void HandleDestruction();

	APlayerController* GetPlayerController()const;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bAlive = true;

private:

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCameraComponent* camera;	

	//FUNCTIONS
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	void Move(float value);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	void Turn(float value);

	//VARIABLES
	UPROPERTY(EditAnywhere, Category = "Movement settings", BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float speed;

	UPROPERTY(EditAnywhere, Category = "Movement settings", BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float turnRate;

	APlayerController* tankPlayerController;
};
