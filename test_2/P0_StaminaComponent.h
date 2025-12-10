// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P0_StaminaComponent.generated.h"


// Delegates for Stamina change and death
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStaminaChanged, float, Stamina, float, MaxStamina, float, Percent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEST_2_API UP0_StaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UP0_StaminaComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing=OnRep_Stamina, EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaRegen = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float DelayBeforeRegen = 5.f;


	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool UseStamina(float LossAmount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RestoreStamina(float RestoreAmount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetCurrentStamina() const { return CurrentStamina; };

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetMaxStamina() const { return MaxStamina; };

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetPercentStamina() const { return CurrentStamina / MaxStamina; };

	UFUNCTION(BlueprintPure, Category = "Stamina")
	bool HasEnoughStamina(float Amount) const { return CurrentStamina >= Amount; };

	UFUNCTION()
	void OnRep_Stamina();

private:
	float TimeSinceLastStaminaUse = 0.f;

	void RegenerateStamina(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
