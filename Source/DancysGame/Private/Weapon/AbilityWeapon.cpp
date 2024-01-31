// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AbilityWeapon.h"

#include "AbilitySystemComponent.h"

AAbilityWeapon::AAbilityWeapon()
{
	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AAbilityWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAbilityWeapon::BeginPlay()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);	
}
