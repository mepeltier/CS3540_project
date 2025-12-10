// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Door.h"
#include  "Net/UnrealNetwork.h"


// Sets default values
AP0_Door::AP0_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicated = true;
	SetReplicateMovement(true);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root.Get());

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(Root.Get());
	DoorFrame->SetCollisionProfileName(TEXT("BlockAll"));

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Root.Get());
	Door->SetCollisionProfileName("BlockAll");

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
}

// Called when the game starts or when spawned
void AP0_Door::BeginPlay()
{
	Super::BeginPlay();

	if (TimelineCurve)
	{
		FOnTimelineFloat Update;
		Update.BindUFunction(this, FName("OnTimelineUpdate"));
		DoorTimeline->AddInterpFloat(TimelineCurve.Get(), Update);
		DoorTimeline->SetLooping(false);
	}
}

void AP0_Door::OnTimelineUpdate(float StartingYaw)
{
	const float DoorYaw = StartingYaw + YawOffset;
	Door->SetRelativeRotation(FRotator(0.f, DoorYaw, 0.f));
}

void AP0_Door::Interact_Implementation(AActor* Caller)
{
	if (!DoorTimeline || !TimelineCurve)
	{
		if (GEngine)
		{
			// if `key` is positive, new messages replace older messages with the same key
			GEngine->AddOnScreenDebugMessage(-1, 1.2, FColor::Red, TEXT("DoorTimeline/Curve missing"));
		}
		return;
	}
	if (bFromStart)
	{
		DoorTimeline->PlayFromStart();
		bFromStart = false;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("DOOR OPENING"));
	}
	else
	{
		DoorTimeline->ReverseFromEnd();
		bFromStart = true;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("DOOR CLOSING"));
	}
}


// Called every frame
void AP0_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
