// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAbilityData.h"
#include "Engine/DataAsset.h"
#include "PlayerAbilitySet.generated.h"

/**
 * 
 */
UCLASS()
class PCG1_API UPlayerAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlayerAbilityData> Abilities;
};
