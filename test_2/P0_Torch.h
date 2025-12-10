// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P0_Torch.generated.h"

UCLASS()
class TEST_2_API AP0_Torch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AP0_Torch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	// Components
	UPROPERTY(VisibleAnywhere, Category="Torch")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* TorchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UPointLightComponent* TorchLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UBoxComponent* TriggerBox;

	// Visible / not visible
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components|State")
	bool bIsLit = false;

	// Events
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedObject, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult);

	void LightTorch();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
