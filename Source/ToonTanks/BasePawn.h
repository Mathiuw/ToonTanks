// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:

	//FUNCTIONS
	void RotateTurret(FVector target);

	UFUNCTION(BlueprintCallable, meta = (allowPrivateAccess = true))
	void Fire();

private:

	//COMPONENTS
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Components", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(EditDefaultsOnly, category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditDefaultsOnly, category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* turretMesh;

	UPROPERTY(EditDefaultsOnly, category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* projectileSpawnPoint;

	//VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* explosionParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* deathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> deathCameraShake;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
