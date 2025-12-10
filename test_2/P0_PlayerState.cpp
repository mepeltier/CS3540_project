// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_PlayerState.h"
#include "Net/UnrealNetwork.h"

AP0_PlayerState::AP0_PlayerState()
{
	bReplicated = true;
	SetReplicateMovement(true);
}
