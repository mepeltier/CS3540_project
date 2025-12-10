// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_DamageArea.h"

#include "P0_HealthComponent.h"

// Sets default values
AP0_DamageArea::AP0_DamageArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	DamageBox = CreateDefaultSubobject<UBoxComponent>("DamageBox");
	DamageBox->SetupAttachment(RootComponent);
	DamageBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	DamageBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DamageBox->SetCollisionResponseToAllChannels(ECR_Overlap);

	DamageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DamageMesh"));
	DamageMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("CubeMesh"));
	if (CubeMesh.Succeeded())
	{
		DamageMesh->SetStaticMesh(CubeMesh.Object);
	}
	DamageMesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	DamageMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AP0_DamageArea::BeginPlay()
{
	Super::BeginPlay();
	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &AP0_DamageArea::OnComponentBeginOverlap);
	DamageBox->OnComponentEndOverlap.AddDynamic(this, &AP0_DamageArea::OnComponentEndOverlap);
}

void AP0_DamageArea::ApplyDamage()
{
	if (OverlappingActor != nullptr)
	{
		if (UP0_HealthComponent* HealthComponent = OverlappingActor->FindComponentByClass<UP0_HealthComponent>())
		{
			HealthComponent->TakeDamage(DamageAmount);
		}
	}
}


void AP0_DamageArea::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (UP0_HealthComponent* HealthComponent = OtherActor->FindComponentByClass<UP0_HealthComponent>())
	{
		OverlappingActor = OtherActor;
		ApplyDamage();
		GetWorldTimerManager().SetTimer(DamageTimer, this, &AP0_DamageArea::ApplyDamage, DamageInterval, true);
	}
}

void AP0_DamageArea::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingActor)
	{
		GetWorldTimerManager().ClearTimer(DamageTimer);
		OverlappingActor = nullptr;
	}
}
