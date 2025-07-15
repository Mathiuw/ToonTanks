// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

APlayerController* ATank::GetPlayerController()const
{
	return tankPlayerController;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	tankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tankPlayerController) 
	{
		FHitResult hitResult;

		//Mouse line trace
		tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

		//Rotate the tank turret
		RotateTurret(hitResult.ImpactPoint);
	} 
}

//Move the tank
void ATank::Move(float value)
{
	FVector deltaLocation = FVector::ZeroVector;
	deltaLocation.X = value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(deltaLocation, true);
}

//Turn the tank
void ATank::Turn(float value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(deltaRotation, true);
}
