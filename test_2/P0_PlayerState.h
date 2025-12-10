// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "P0_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2_API AP0_PlayerState : public APlayerState
{
	GENERATED_BODY()
	AP0_PlayerState();

private:
	bool bReplicated;
	
};
