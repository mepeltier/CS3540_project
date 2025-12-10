// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_GameInstance.h"

#include "Kismet/GameplayStatics.h"

void UP0_GameInstance::HostGame(const FString& MapName)
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, FName(*MapName), true, TEXT("opening"));
	// FString TravelURL = MapName + TEXT("?listen");
	// World->ServerTravel(TravelURL, true);
}

void UP0_GameInstance::JoinGame(const FString& HostAddress)
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (!PlayerController) { return; }

	PlayerController->ClientTravel(HostAddress, TRAVEL_Absolute);
}
