// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Campfire.h"

#include "NiagaraComponent.h"

// Sets default values
AP0_Campfire::AP0_Campfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CampfireBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Campfire"));
	CampfireBase->SetupAttachment(Root);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(CampfireBase);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(CampfireBase);

}

// Called when the game starts or when spawned
void AP0_Campfire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP0_Campfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AP0_Campfire::Interact_Implementation(AActor* Caller)
{
	PointLight->ToggleVisibility();
	FireEffect->ToggleVisibility();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Toggling campfire"));
}
