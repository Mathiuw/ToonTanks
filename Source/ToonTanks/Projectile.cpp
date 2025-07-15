// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = projectileStaticMesh;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	projectileMovementComponent->MaxSpeed = 1500.f;
	projectileMovementComponent->InitialSpeed = 1500.f;

	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	particleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileStaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& hit)
{
	//DEBUG log
	UE_LOG(LogTemp, Warning, TEXT("Projectile hit"));

	auto owner = GetOwner();

	if (owner == nullptr) return;
	
	AController* instigator = owner->GetInstigatorController();

	if (otherActor && otherActor != this && otherActor != owner)
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, instigator, this, UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Damage taken"));
	}

	if(hitParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticles, GetActorTransform());

	if (explosionSound) UGameplayStatics::PlaySoundAtLocation(this, explosionSound, GetActorLocation());

	if (hitCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);

	Destroy();
}

