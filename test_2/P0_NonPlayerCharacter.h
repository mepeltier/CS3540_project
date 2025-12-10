// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "P0_Interactable.h"
#include "GameFramework/Pawn.h"
#include "P0_NonPlayerCharacter.generated.h"

UCLASS()
class TEST_2_API AP0_NonPlayerCharacter : public APawn, public IP0_Interactable
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(AActor* Caller) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Sets default values for this pawn's properties
	AP0_NonPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere, Category="NPC")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category="NPC")
	TObjectPtr<UStaticMeshComponent> NPCBody;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
