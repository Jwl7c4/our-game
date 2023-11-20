// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include <DancysGame.h>

#include "DancysGameplayAbility.generated.h"

/**
 *
 */
UCLASS()
class DANCYSGAME_API UDancysGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UDancysGameplayAbility();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Id")
	EAbilityInput AbilityInputId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Id")
	EAbilityInput AbilityId;

};
