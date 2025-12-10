// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P0_Interactable.h"
#include "GameFramework/Actor.h"
#include "P0_HealingObject.generated.h"

UCLASS()
class TEST_2_API AP0_HealingObject : public AActor, public IP0_Interactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AP0_HealingObject();

	virtual void Interact_Implementation(AActor* Caller) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere, Category="NPC")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category="NPC")
	TObjectPtr<UStaticMeshComponent> Body;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float HealAmount = 20;
};
