// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P0_Interactable.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "P0_Light.generated.h"

UCLASS()
class TEST_2_API AP0_Light : public AActor, public IP0_Interactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AP0_Light();

	virtual void Interact_Implementation(AActor* Caller) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category="Light")
	TObjectPtr<USceneComponent> Root;
	

	UPROPERTY(VisibleAnywhere, Category = "Light")
	TObjectPtr<UPointLightComponent> PointLight;
	
};
