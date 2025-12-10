// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Passthrough.h"

// Sets default values
AP0_Passthrough::AP0_Passthrough()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root.Get());

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMesh->SetupAttachment(Root.Get());
	ObjectMesh->SetCollisionProfileName(TEXT("Ignore"));
}

// Called when the game starts or when spawned
void AP0_Passthrough::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP0_Passthrough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
