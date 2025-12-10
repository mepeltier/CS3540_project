// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_GameState.h"
#include "Net/UnrealNetwork.h"

AP0_GameState::AP0_GameState()
{
	bReplicated = true;
	SetReplicateMovement(bReplicated);
}
