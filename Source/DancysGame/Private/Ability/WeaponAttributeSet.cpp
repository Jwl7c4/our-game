// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/WeaponAttributeSet.h"

#include "Net/UnrealNetwork.h"

UWeaponAttributeSet::UWeaponAttributeSet()
{
	Health = 0.0f;
	MaxHealth = Health;
	HealthRegenRate = 0.f;
}

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
}

void UWeaponAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, MaxHealth, OldMaxHealth);
}

void UWeaponAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Health, OldHealth);
}

void UWeaponAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, HealthRegenRate, OldHealthRegenRate);
}