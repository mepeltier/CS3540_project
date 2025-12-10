// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_DialogueButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UP0_DialogueButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChoiceButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Yes choice button"));

		ChoiceButton->OnClicked.AddDynamic(this, &UP0_DialogueButton::OnButtonClicked);
	}
}

void UP0_DialogueButton::ConstructChoice(const FText& ChosenText, int32 InNextDialogueID)
{
	if (ChoiceText)
	{
		ChoiceText->SetText(ChosenText);
	}
	NextDialogueID = InNextDialogueID;
}

void UP0_DialogueButton::OnButtonClicked()
{
	OnChoiceSelected.Broadcast(NextDialogueID);
}
