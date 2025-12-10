// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "P0_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEST_2_API AP0_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AP0_GameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
