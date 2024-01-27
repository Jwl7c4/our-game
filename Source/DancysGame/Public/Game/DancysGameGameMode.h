// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "DancysGameGameMode.generated.h"

UCLASS(minimalapi)
class ADancysGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADancysGameGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACharacter> PawnClass;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
