// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P0_PlayerStatsWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AP0_Character;

/**
 * 
 */
UCLASS()
class TEST_2_API UP0_PlayerStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(Meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(Meta = (BindWidgetOptional))
	UTextBlock* HealthText;

	UPROPERTY(Meta = (BindWidgetOptional))
	UTextBlock* StaminaText;

private:
	UPROPERTY()
	AP0_Character* OwnerPlayer;

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth, float HealthPercent);

	UFUNCTION()
	void OnStaminaChanged(float Stamina, float MaxStamina, float StaminaPercent);
};
