// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	toonTanksGameMode = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser)
{
	if (damage <= 0.f) return;

	health -= damage;

	if (health <= 0.f && toonTanksGameMode)
	{
		toonTanksGameMode->ActorDied(GetOwner());
	}

	UE_LOG(LogTemp, Warning, TEXT("%s health: %f"), *GetOwner()->GetName(), health);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

