// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Light.h"

// Sets default values
AP0_Light::AP0_Light()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root.Get());

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = 3000.0f;
	PointLight->SetupAttachment(Root.Get());
}

// Called when the game starts or when spawned
void AP0_Light::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP0_Light::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP0_Light::Interact_Implementation(AActor* Caller)
{
	PointLight->ToggleVisibility();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Toggling light"));
}
