// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "AbilitySystemInterface.h"

#include "AbilityWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DANCYSGAME_API AAbilityWeapon : public AWeapon, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAbilityWeapon();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay();

protected:

	class UAbilitySystemComponent* AbilitySystemComponent;
};
