// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/WeaponBase.h"
#include "PlayerEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquiped, AWeaponBase*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequiped, AWeaponBase*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponAdded, AWeaponBase*, weapon, int32, index);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PCG1_API UPlayerEquipment : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<FActiveGameplayEffectHandle> WeaponGameplayEffects;
	
public:
	// Sets default values for this component's properties
	UPlayerEquipment();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool EquipOnPickup = false;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AWeaponBase* CurrentWeapon;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AWeaponBase*> AllWeapons;

	UPROPERTY(BlueprintAssignable)
	FOnWeaponEquiped OnWeaponEquiped;
	UPROPERTY(BlueprintAssignable)
	FOnWeaponUnequiped OnWeaponUnequiped;
	UPROPERTY(BlueprintAssignable)
	FOnWeaponAdded OnWeaponAdded;
protected:
	UFUNCTION(BlueprintCallable)
	void GrantEffects();
	
public:

	UFUNCTION(BlueprintCallable)
	void AddWeapon(AWeaponBase* weapon);


	UFUNCTION(BlueprintCallable)
	UAbilitySystemComponent* GetASC() const;
	
	
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int index);
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();


	
};
