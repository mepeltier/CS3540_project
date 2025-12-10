// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_InteractionComponent.h"

#include "P0_Interactable.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP0_InteractionComponent::UP0_InteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UP0_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UP0_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UP0_InteractionComponent::LineTraceInteract()
{
	// TODO see 11/19 lecture for multiplayer code changes
	AActor* InteractOwner = GetOwner();

	if (!InteractOwner) { return; }

	// eye location for line tracing
	FVector EyeLocation;
	FRotator EyeRotation;
	InteractOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	const FVector EndOfLineTrace = EyeLocation + EyeRotation.Vector() * TraceDistance;

	// perform line tracing
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(InteractTrace), false, InteractOwner);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndOfLineTrace, TraceChannel,
	                                                       CollisionQueryParams);
	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), EyeLocation, EndOfLineTrace, bHit ? FColor::Green : FColor::Red,
		              false, 1.f, 0, 1.5f);
		if (bHit)
		{
			DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 8.f, FColor::Yellow, false, 1.f);
		}
	}

	if (!bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Called line trace interact, didn't hit");

		return;
	}

	if (AActor* Target = HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hit something");
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, Target->GetClass()->GetFullName());


		if (Target->GetClass()->ImplementsInterface(UP0_Interactable::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Implements interactable");

			APawn* OwnerAsPawn = Cast<APawn>(InteractOwner);
			IP0_Interactable::Execute_Interact(Target, OwnerAsPawn);
		}
	}
}

void UP0_InteractionComponent::PerformServerInteraction()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) { return; }

	FHitResult HitResult;
	LineTraceInteract();
}

void UP0_InteractionComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
