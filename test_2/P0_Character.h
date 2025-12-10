// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "P0_HealthComponent.h"
#include "P0_PlayerStatsWidget.h"

#include "P0_Character.generated.h"


class UP0_InteractionComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class UP0_HealthComponent;
class UP0_StaminaComponent;

UCLASS()
class TEST_2_API AP0_Character : public ACharacter
{
public:
	GENERATED_BODY()

	// Sets default values for this character's properties
	AP0_Character();

protected:
	/*
	 This is a comment
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputMappingContext> InputMappingContextDefault;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	TObjectPtr<UP0_InteractionComponent> InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AP0_ThrownProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FVector ProjectileSpawnOffset = FVector(100.0f, 00.0, 100.0f);

	// Health and Stamina Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	UP0_HealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	UP0_StaminaComponent* StaminaComp;


	/** The Input Action for moving. You will assign IA_Move to this in your Character Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	/* The Input Action for look. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> LookAction;

	/** The Input Action for jumping. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> JumpAction;

	/** The Input Action for running. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> RunAction;

	/** The Input Action for interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> InteractAction;

	/** The Input Action for interaction. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> ShootAction;

	// UI Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UP0_PlayerStatsWidget> StatsWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	UP0_PlayerStatsWidget* StatsWidget;

	// Attribute Cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Attributes")
	float ProjectileCost = 5.f;

	bool bIsRunning = false;

	/** Function to handle the inputs */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ShootProjectile(const FInputActionValue& Value);
	void Run();
	void StopRun();
	void Interact();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attribute Accessors
	UFUNCTION(BlueprintPure, Category="Components")
	UP0_HealthComponent* GetHealthComp() const { return HealthComp; }

	UFUNCTION(BlueprintPure, Category="Components")
	UP0_StaminaComponent* GetStaminaComp() const { return StaminaComp; }

	UFUNCTION(Server, Reliable)
	void ServerInteract();
	
	UFUNCTION(Server, Reliable)
	void ServerShootProjectile(FVector SpawnLocation, FRotator SpawnRotation);

	// UFUNCTION(NetMulticast, Unreliable)
	// void MulticastPlay();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	bool bReplicated;
};
