// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/DancysGameGameMode.h"
#include "Character/DancysGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADancysGameGameMode::ADancysGameGameMode()
{
}

void ADancysGameGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	if (PawnClass != NULL)
	{
		DefaultPawnClass = PawnClass;
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("InitGame - No player pawn class selected"));
	}

	Super::InitGame(MapName, Options, ErrorMessage);
}
