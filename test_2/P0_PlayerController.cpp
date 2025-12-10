// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_PlayerController.h"

#include "P0_GameInstance.h"
#include "Components/Button.h"

void AP0_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (bIsInGame) { return; }

	if (MainMenuWidgetClass && IsLocalController())
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			SetInputMode(InputMode);
			bShowMouseCursor = true;

			UButton* HostButton = Cast<UButton>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("HostButton")));
			if (HostButton)
			{
				HostButton->OnClicked.AddDynamic(this, &AP0_PlayerController::OnHostClicked);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HostButton not found"));
			}

			UButton* JoinButton = Cast<UButton>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("JoinButton")));
			if (JoinButton)
			{
				JoinButton->OnClicked.AddDynamic(this, &AP0_PlayerController::OnJoinClicked);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("JoinButton not found"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create MainMenuWidgetInstance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenuWidgetClass not set or not local controller"));
	}
}

void AP0_PlayerController::OnHostClicked()
{
	bIsInGame = true;
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
		UE_LOG(LogTemp, Log, TEXT("MainMenuWidgetInstance removed on HostClicked"));
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	UP0_GameInstance* GameInstance = Cast<UP0_GameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->HostGame("LevelSample");
	}
}

void AP0_PlayerController::OnJoinClicked()
{
	bIsInGame = true;
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
		UE_LOG(LogTemp, Log, TEXT("MainMenuWidgetInstance removed on JoinClicked"));
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	UP0_GameInstance* GameInstance = Cast<UP0_GameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->JoinGame("127.0.0.1");
	}
}
