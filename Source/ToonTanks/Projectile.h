// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//COMPONENTS
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true));
	UStaticMeshComponent* projectileStaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* projectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystemComponent* particleSystemComponent;

	//FUNCTIONS
	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& hit);

	//VARIABLES
	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	UParticleSystem* hitParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* launchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* explosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> hitCameraShakeClass;
};
