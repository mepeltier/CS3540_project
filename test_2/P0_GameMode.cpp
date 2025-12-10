// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_GameMode.h"
#include "P0_GameState.h"
#include "P0_PlayerController.h"
#include "P0_PlayerState.h"

AP0_GameMode::AP0_GameMode()
{
	GameStateClass = AP0_GameState::StaticClass();
	// PlayerControllerClass = AP0_PlayerController::StaticClass();
	PlayerStateClass = AP0_PlayerState::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BP_PlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	bUseSeamlessTravel = true;
}



void AP0_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AP0_GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}
