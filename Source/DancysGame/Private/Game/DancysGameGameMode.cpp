// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/DancysGameGameMode.h"
#include "Character/DancysGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADancysGameGameMode::ADancysGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DancysGame/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
