// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_ThrownProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include  "Net/UnrealNetwork.h"


// Sets default values
AP0_ThrownProjectile::AP0_ThrownProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicated = true;
	SetReplicateMovement(true);

	// Create sphere collision component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSphereRadius(3.0f);
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollision->SetNotifyRigidBodyCollision(true);

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereCollision);

	// Projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.9f;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void AP0_ThrownProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP0_ThrownProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AP0_ThrownProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || OtherActor == this || OtherActor == GetOwner()) { return; }
	if (!GetOwner()->HasAuthority()) { return; }

	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		FVector ImpulseDirection = GetVelocity().GetSafeNormal();
		OtherComp->AddImpulseAtLocation(
			ImpulseDirection * ImpulseStrength, Hit.Location);
	}

	if (AGeometryCollectionActor* GeoActor = Cast<AGeometryCollectionActor>(OtherActor))
	{
		if (UGeometryCollectionComponent* GeoComp = GeoActor->GetGeometryCollectionComponent())
		{
			FVector ImpulseDirection = GetVelocity().GetSafeNormal();
			float BreakingForce = ImpulseStrength * 10000.0f;
			GeoComp->ApplyBreakingLinearVelocity(-1, ImpulseDirection * BreakingForce);
		}
	}

	// Destroys the projectile
	Destroy();
}


void AP0_ThrownProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                          AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                          int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
}
