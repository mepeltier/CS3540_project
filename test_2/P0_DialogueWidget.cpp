// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_DialogueWidget.h"
#include "P0_DialogueWidget.h"

#include "HeadMountedDisplayTypes.h"
#include "P0_DialogueButton.h"
#include "P0_PlayerController.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UP0_DialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UP0_DialogueWidget::StartDialogue(UDataTable* InDialogueTable, int32 StartingDialogueID)
{
	UE_LOG(LogTemp, Warning, TEXT("UP0_DialogueWidget::StartDialogue"));

	DialogueTable = InDialogueTable;

	if (!DialogueTable)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueTable is null"));
		return;
	}
	SetVisibility(ESlateVisibility::Visible);

	if (AP0_PlayerController* Owner = Cast<AP0_PlayerController>(GetOwningPlayer()))
	{
		UE_LOG(LogTemp, Warning, TEXT("UP0_DialogueWidget::StartDialogue : If Owner"));

		FInputModeUIOnly InputMode;
		// InputMode.SetWidgetToFocus(TakeWidget());
		// InputMode.SetWidgetToFocus(this->GetCachedWidget());
		// Owner->SetInputMode(InputMode);
		// Owner->bShowMouseCursor = true;
	}

	DisplayDialogue(StartingDialogueID);
}

void UP0_DialogueWidget::DisplayDialogue(int32 DialogueID)
{
	UE_LOG(LogTemp, Warning, TEXT("UP0_DialogueWidget::DisplayDialogue"));

	if (!DialogueTable) { return; }

	FString Context;
	FName RowName = FName(*FString::FromInt(DialogueID));
	FDialogueEntry* Entry = DialogueTable->FindRow<FDialogueEntry>(RowName, Context);
	if (!Entry)
	{
		UE_LOG(LogTemp, Error, TEXT("Entry not found"));
		return;
	}
	if (NPCName)
	{
		NPCName->SetText(Entry->NPCName);
	}
	if (DialogueText)
	{
		DialogueText->SetText(Entry->DialogueText);
	}

	ClearChoices();

	if (Entry->DialogueChoices.Num() == -1)
	{
		EndDialogue();
		return;
	}

	for (const FDialogueChoice& Choice : Entry->DialogueChoices)
	{
		UP0_DialogueButton* Button = CreateChoiceButton(Choice);

		if (Button && ChoicesContainer)
		{
			UE_LOG(LogTemp, Display, TEXT("Yes button and choice container"));

			ChoicesContainer->AddChild(Button);
		}
	}
}

UP0_DialogueButton* UP0_DialogueWidget::CreateChoiceButton(const FDialogueChoice Choice)
{
	UE_LOG(LogTemp, Warning, TEXT("Creating ChoiceButton"));

	if (!DialogueButtonClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No DialogueButtonClass"));
		return nullptr;
	}

	UP0_DialogueButton* NewButton = CreateWidget<UP0_DialogueButton>(this, DialogueButtonClass);
	if (!NewButton)
	{
		UE_LOG(LogTemp, Error, TEXT("No NewButton"));
		return nullptr;
	}

	NewButton->ConstructChoice(Choice.ChoiceText, Choice.NextDialogue);

	NewButton->OnChoiceSelected.AddDynamic(this, &UP0_DialogueWidget::OnChoiceClicked);
	return NewButton;
}

void UP0_DialogueWidget::OnChoiceClicked(int32 NextDialogueID)
{
	if (NextDialogueID == -1)
	{
		EndDialogue();
	}
	else
	{
		DisplayDialogue(NextDialogueID);
	}
}

void UP0_DialogueWidget::ClearChoices()
{
	if (ChoicesContainer)
		ChoicesContainer->ClearChildren();
}

void UP0_DialogueWidget::EndDialogue()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (AP0_PlayerController* Owner = Cast<AP0_PlayerController>(GetOwningPlayer()))
	{
		FInputModeGameOnly InputMode;
		Owner->SetInputMode(InputMode);
		Owner->bShowMouseCursor = false;
	}
	OnDialogueEnded.Broadcast();
}
