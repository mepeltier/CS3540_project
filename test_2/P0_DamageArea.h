// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "P0_DamageArea.generated.h"

UCLASS()
class TEST_2_API AP0_DamageArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AP0_DamageArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* DamageBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DamageMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DamageAmount = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DamageInterval = 1.f;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

private:
	FTimerHandle DamageTimer;

	UPROPERTY()
	AActor* OverlappingActor;

	void ApplyDamage();
};
