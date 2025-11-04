// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilitites/PlayerAbilityData.h"
#include "Abilitites/PlayerAbilitySet.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class PCG1_API UWeaponData : public UPlayerAbilitySet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimInstanceClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> GrantedEffects;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeed;
	
};
