// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P0_Interactable.h"
#include "Components/TimelineComponent.h"
#include "P0_Door.generated.h"

UCLASS()
class TEST_2_API AP0_Door : public AActor, public IP0_Interactable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float MaxYaw;

	void Interact_Implementation(AActor* Caller) override;

	// Sets default values for this actor's properties
	AP0_Door();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere, Category="Door")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category="Door")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, Category="Door")
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditAnywhere, Category="Door|Timeline")
	float YawOffset = 0.f;

	// Timeline
	UPROPERTY(VisibleAnywhere, Category="Door|Timeline")
	TObjectPtr<UTimelineComponent> DoorTimeline;

	UPROPERTY(EditAnywhere, Category="Door|Timeline")
	TObjectPtr<UCurveFloat> TimelineCurve = nullptr;

	UFUNCTION()
	void OnTimelineUpdate(float StartingYaw);

	// rotate from starting point (open) or reverse (closed)
	bool bFromStart = true;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bReplicated;
};
