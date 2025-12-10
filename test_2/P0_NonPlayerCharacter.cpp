// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_NonPlayerCharacter.h"

// Sets default values
AP0_NonPlayerCharacter::AP0_NonPlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root.Get());

	NPCBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NPCBody"));
	NPCBody->SetupAttachment(Root.Get());
	NPCBody->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void AP0_NonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AP0_NonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP0_NonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AP0_NonPlayerCharacter::Interact_Implementation(AActor* Caller)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2, FColor::Green, TEXT("Hello!"));
}
