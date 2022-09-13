// Copyright Epic Games, Inc. All Rights Reserved.

#include "A1GameMode.h"
#include "A1HUD.h"
#include "A1Character.h"
#include "UObject/ConstructorHelpers.h"

AA1GameMode::AA1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AA1HUD::StaticClass();
}
