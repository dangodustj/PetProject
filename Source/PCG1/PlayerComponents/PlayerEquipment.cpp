// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEquipment.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"


// Sets default values for this component's properties
UPlayerEquipment::UPlayerEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentWeapon = nullptr;
	// ...
}

UAbilitySystemComponent* UPlayerEquipment::GetASC() const
{
	if (GetOwner()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface*a= Cast<IAbilitySystemInterface>(GetOwner());
		return a->GetAbilitySystemComponent();
	}
	return nullptr;
}

void UPlayerEquipment::AddWeapon(AWeaponBase* weapon)
{
	int32 index = AllWeapons.AddUnique(weapon);
	OnWeaponAdded.Broadcast(weapon, index);
	if (EquipOnPickup)
	{
		EquipWeapon(AllWeapons.Num() -1);
	}
}


void UPlayerEquipment::EquipWeapon(int index)
{
	if (IsValid(CurrentWeapon))
	{
		UnequipWeapon();
	}
	CurrentWeapon = AllWeapons[index];
	
	GrantEffects();
	OnWeaponEquiped.Broadcast(CurrentWeapon);
}

void UPlayerEquipment::UnequipWeapon()
{
	UAbilitySystemComponent* ASC = GetASC();
	if (IsValid(ASC))
	{
		for (auto effect : WeaponGameplayEffects)
		{
			ASC->RemoveActiveGameplayEffect(effect);
		}
		WeaponGameplayEffects.Empty();
	}
	OnWeaponUnequiped.Broadcast(CurrentWeapon);
	CurrentWeapon = nullptr;
}

void UPlayerEquipment::GrantEffects()
{
	UAbilitySystemComponent* ASC = GetASC();
	if (!IsValid(ASC)) return;

	for (auto effect : CurrentWeapon->GetEffects())
	{
		FActiveGameplayEffectHandle handle = ASC->ApplyGameplayEffectToSelf(effect.GetDefaultObject(), 1, ASC->MakeEffectContext());
		
		WeaponGameplayEffects.Add(handle);
	}
}






