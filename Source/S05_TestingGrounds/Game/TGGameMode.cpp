// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGGameMode.h"
#include "Player/TGHUD.h"
#include "Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATGGameMode::ATGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Player/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATGHUD::StaticClass();
}
