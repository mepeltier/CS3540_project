// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P0_DialogueWidget.h"
#include "P0_Interactable.h"
#include "P0_PlayerController.h"
#include "GameFramework/Character.h"
#include  "Net/UnrealNetwork.h"
#include "P0_NPCCharacter.generated.h"


class UP0_DialogueWidget;
class USphereComponent;
class UDataTable;
class AP0_Character;

UCLASS()
class TEST_2_API AP0_NPCCharacter : public ACharacter, public IP0_Interactable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP0_NPCCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Component")
	USphereComponent* InteractionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* DialogueTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 StartDialogueID;

	UPROPERTY(EditDefaultsOnly, Category="Dialogue")
	TSubclassOf<UP0_DialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	UP0_DialogueWidget* DialogueWidget;

	UPROPERTY(Replicated)
	AP0_Character* InteractingPlayer;

	UFUNCTION()
	void OnInteractionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact_Implementation(AActor* Caller) override;

	UFUNCTION(Server, Reliable)
	void ServerStartDialogue(AP0_Character* Caller);

private:
	UFUNCTION()
	void OnDialogueEnded();

	UFUNCTION()
	void StartDialogue();

	bool bReplicated;
	bool isDialogueActive;
};
