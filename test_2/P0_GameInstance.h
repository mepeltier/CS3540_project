// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "P0_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2_API UP0_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Multiplayer")
	void HostGame(const FString& MapName);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer")
	void JoinGame(const FString& HostAddress);
};
