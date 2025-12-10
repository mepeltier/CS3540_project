// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_HealingObject.h"

#include "P0_Character.h"
#include "P0_HealthComponent.h"

// Sets default values
AP0_HealingObject::AP0_HealingObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root.Get());

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Root.Get());
	Body->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void AP0_HealingObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP0_HealingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP0_HealingObject::Interact_Implementation(AActor* Caller)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2, FColor::Purple, TEXT("Restoring Health"));

	if (Caller != nullptr)
	{
		if (UP0_HealthComponent* HealthComponent = Caller->FindComponentByClass<UP0_HealthComponent>())
		{
			HealthComponent->Heal(HealAmount);
		}
	}
	this->Destroy();
}
