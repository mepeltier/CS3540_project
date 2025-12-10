// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_HealthComponent.h"

#include "NiagaraTypes.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP0_HealthComponent::UP0_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UP0_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// CurrentHealth = MaxHealth;

	SetHealth(MaxHealth);
}

void UP0_HealthComponent::TakeDamage(float DamageAmount)
{
	if (!GetOwner()->HasAuthority() || isCharacterDead || DamageAmount <= 0) { return; }
	SetHealth(CurrentHealth - DamageAmount);
}

void UP0_HealthComponent::Heal(float HealAmount)
{
	if (isCharacterDead || HealAmount <= 0) { return; }
	SetHealth(CurrentHealth + HealAmount);
}

void UP0_HealthComponent::SetHealth(float NewHealth)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority()) { return; }
	CurrentHealth = FMath::Clamp(NewHealth, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, GetPercentHealth());

	// If this kills us, broadcast death
	if (CurrentHealth <= 0.f && !isCharacterDead)
	{
		isCharacterDead = true;
		OnDeath.Broadcast();
	}
}

void UP0_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UP0_HealthComponent, CurrentHealth);

	// DOREPLIFETIME(UP0_HealthComponent, isDead());
}

void UP0_HealthComponent::OnReplicatedCurrentHealth()
{
	// if health is updated by the server
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, GetPercentHealth());

	if (CurrentHealth <= 0.f && !isCharacterDead)
	{
		isCharacterDead = true;
		OnDeath.Broadcast();
	}
}
