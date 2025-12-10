// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Projectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
AP0_Projectile::AP0_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere collision component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSphereRadius(3.0f);
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollision->SetNotifyRigidBodyCollision(true);

	// Niagara component for VFX
	ProjectileEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileEffect"));
	ProjectileEffect->SetupAttachment(RootComponent);

	// Projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AP0_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp,
                           FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || OtherActor == this || OtherActor == GetOwner()) return;

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
			float BreakingForce = ImpulseStrength * 100.0f;
			GeoComp->ApplyBreakingLinearVelocity(-1, ImpulseDirection * BreakingForce);
		}
	}

	// Destroys the projectile
	Destroy();
}


void AP0_Projectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
}

// Called when the game starts or when spawned
void AP0_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentHit.AddDynamic(this, &AP0_Projectile::OnHit);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AP0_Projectile::OnBeginOverlap);
}

// Called every frame
void AP0_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
