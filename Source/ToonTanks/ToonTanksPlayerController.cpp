// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	//Enable/disable input
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	//Enable/disable mouse cursor
	bShowMouseCursor = bPlayerEnabled;
}
