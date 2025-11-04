#pragma once
#include "CoreMinimal.h"
#include "InputAction.h"
#include "Abilities/GameplayAbility.h"
#include "PlayerComponents/PlayerInputComponent.h"
#include "PlayerAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Ability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputActionID InputID;
};
