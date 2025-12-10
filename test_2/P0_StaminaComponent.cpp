// Fill out your copyright notice in the Description page of Project Settings.

#include "P0_StaminaComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP0_StaminaComponent::UP0_StaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UP0_StaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// CurrentStamina = MaxStamina;
	SetStamina(MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina, GetPercentStamina());
}

bool UP0_StaminaComponent::UseStamina(float LossAmount)
{
	if (LossAmount <= 0) { return true; }
	if (!GetOwner()->HasAuthority()) { return false; }
	AActor* Owner = GetOwner();

	if (CurrentStamina >= LossAmount)
	{
		if (Owner && Owner->HasAuthority())
		{
			SetStamina(CurrentStamina - LossAmount);
			TimeSinceLastStaminaUse = 0.f;
		}
		return true;
	}
	return false;
}

void UP0_StaminaComponent::RestoreStamina(float RestoreAmount)
{
	if (RestoreAmount <= 0) { return; }
	SetStamina(CurrentStamina + RestoreAmount);
}

void UP0_StaminaComponent::SetStamina(float NewStamina)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority()) { return; }

	CurrentStamina = FMath::Clamp(NewStamina, 0, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina, GetPercentStamina());
}

void UP0_StaminaComponent::RegenerateStamina(float DeltaTime)
{
	TimeSinceLastStaminaUse += DeltaTime;
	AActor* Owner = GetOwner();
	if (TimeSinceLastStaminaUse >= DelayBeforeRegen && CurrentStamina < MaxStamina)
	{
		if (Owner && Owner->HasAuthority())
		{
			SetStamina(CurrentStamina + StaminaRegen);
			TimeSinceLastStaminaUse = DelayBeforeRegen / 2;
		}
	}
}


void UP0_StaminaComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	RegenerateStamina(DeltaTime);
}

void UP0_StaminaComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UP0_StaminaComponent, CurrentStamina);
}

void UP0_StaminaComponent::OnRep_Stamina()
{
	// server stamina update
	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina, GetPercentStamina());
}
