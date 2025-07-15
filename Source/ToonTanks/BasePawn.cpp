// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components constructor
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule collider"));
	RootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projecxtile spawn point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::HandleDestruction()
{
	//Spawn explosion particle on death
	if (explosionParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticle, GetActorTransform());

	//Play explosion sound
	if (deathSound) UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());

	if (deathCameraShake) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShake);
}

void ABasePawn::RotateTurret(FVector target)
{
	FVector lookVector = target - turretMesh->GetComponentLocation();
	FRotator lookRotation(0, lookVector.Rotation().Yaw, 0);

	turretMesh->SetWorldRotation
	(
		FMath::RInterpTo
		(
			turretMesh->GetComponentRotation(), 
			lookRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			10.f
		)
	);
}

void ABasePawn::Fire()
{
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, projectileSpawnPoint->GetComponentTransform());

	projectile->SetOwner(this);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

