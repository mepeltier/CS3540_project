// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P0_Interactable.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "P0_Campfire.generated.h"

UCLASS()
class TEST_2_API AP0_Campfire : public AActor, public IP0_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP0_Campfire();

	virtual void Interact_Implementation(AActor* Caller) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UNiagaraComponent* FireEffect;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> CampfireBase;

};
