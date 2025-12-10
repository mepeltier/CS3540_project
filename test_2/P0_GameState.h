// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "P0_GameState.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2_API AP0_GameState : public AGameState
{
	GENERATED_BODY()
	AP0_GameState();

private:
	bool bReplicated;
};
