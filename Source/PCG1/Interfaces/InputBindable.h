// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputBindable.generated.h"

struct FInputActionValue;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UInputBindable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PCG1_API IInputBindable
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupInput(UEnhancedInputComponent* InputComponent);

};
