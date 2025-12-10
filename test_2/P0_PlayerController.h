// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P0_Character.h"
#include "P0_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2_API AP0_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** The Input Mapping Context to use. Assign IMC_Default to this in your Player Controller Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
 
	UPROPERTY()
	UUserWidget* MainMenuWidgetInstance;

	UFUNCTION()
	void OnHostClicked();
 
	UFUNCTION()
	void OnJoinClicked();

	bool bIsInGame = false;

};
