// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue.h"
#include "P0_DialogueButton.h"
#include "P0_DialogueWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UVerticalBox;
class UDialogueButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

UCLASS()
class TEST_2_API UP0_DialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(UDataTable* InDialogueTable, int32 StartingDialogueID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EndDialogue();

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueEnded OnDialogueEnded;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NPCName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ChoicesContainer;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TSubclassOf<UP0_DialogueButton> DialogueButtonClass;

private:
	UPROPERTY()
	UDataTable* DialogueTable;

	void DisplayDialogue(int32 NextDialogueID);
	void ClearChoices();

	UFUNCTION()
	void OnChoiceClicked(int32 NextDialogueID);

	UP0_DialogueButton* CreateChoiceButton(const FDialogueChoice Choice);
};
