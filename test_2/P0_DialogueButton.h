// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P0_DialogueButton.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChoiceSelected, int32, NextDialogueID);

UCLASS()
class TEST_2_API UP0_DialogueButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void ConstructChoice(const FText& ChosenText, int32 NextDialogueID);

	UPROPERTY(BlueprintAssignable, Category="Dialogue")
	FOnChoiceSelected OnChoiceSelected;

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* ChoiceButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ChoiceText;

private:
	int32 NextDialogueID;

	UFUNCTION()
	void OnButtonClicked();
};
