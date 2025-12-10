// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_PlayerStatsWidget.h"

#include "P0_Character.h"
#include "P0_HealthComponent.h"
#include "P0_StaminaComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UP0_PlayerStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerPlayer = Cast<AP0_Character>(GetOwningPlayerPawn());
	if (OwnerPlayer)
	{
		if (UP0_HealthComponent* HealthComponent = OwnerPlayer->GetHealthComp())
		{
			HealthComponent->OnHealthChanged.AddDynamic(this, &UP0_PlayerStatsWidget::OnHealthChanged);
			OnHealthChanged(HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth(),
			                HealthComponent->GetPercentHealth());
		}
		if (UP0_StaminaComponent* StaminaComponent = OwnerPlayer->GetStaminaComp())
		{
			StaminaComponent->OnStaminaChanged.AddDynamic(this, &UP0_PlayerStatsWidget::OnStaminaChanged);
			OnStaminaChanged(StaminaComponent->GetCurrentStamina(), StaminaComponent->GetMaxStamina(),
			                 StaminaComponent->GetPercentStamina());
		}
	}

	if (HealthBar)
	{
		HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
	}
	if (StaminaBar)
	{
		StaminaBar->SetFillColorAndOpacity(FLinearColor::Blue);
	}
}

void UP0_PlayerStatsWidget::NativeDestruct()
{
	// destruct - unbind from component event
	if (OwnerPlayer)
	{
		if (UP0_HealthComponent* HealthComponent = OwnerPlayer->GetHealthComp())
		{
			HealthComponent->OnHealthChanged.RemoveDynamic(this, &UP0_PlayerStatsWidget::OnHealthChanged);
		}
		if (UP0_StaminaComponent* StaminaComponent = OwnerPlayer->GetStaminaComp())
		{
			StaminaComponent->OnStaminaChanged.RemoveDynamic(this, &UP0_PlayerStatsWidget::OnStaminaChanged);
		}
	}
	Super::NativeDestruct();
}

void UP0_PlayerStatsWidget::OnHealthChanged(float Health, float MaxHealth, float HealthPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}
	if (HealthText)
	{
		FString HealthString = FString::Printf(TEXT("%.2f/%.2f"), Health, MaxHealth);
		HealthText->SetText(FText::FromString(HealthString));
	}
}

void UP0_PlayerStatsWidget::OnStaminaChanged(float Stamina, float MaxStamina, float StaminaPercent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(StaminaPercent);
	}
	if (StaminaText)
	{
		FString StaminaString = FString::Printf(TEXT("%.2f/%.2f"), Stamina, MaxStamina);
		StaminaText->SetText(FText::FromString(StaminaString));
	}
}
