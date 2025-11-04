// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "EnhancedInputComponent.h"
#include "Abilitites/PlayerAbilitySet.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interfaces/InputBindable.h"
#include "AbilityManagerComponent.generated.h"

struct FInputBindsContainer
{
	FEnhancedInputActionEventBinding& PressedBinding;
	FEnhancedInputActionEventBinding& ReleasedBinding;
};

USTRUCT()
struct FAbilitySubscriptionData
{
	GENERATED_BODY()
	FGameplayAbilitySpec AbilitySpec;
	FGameplayMessageListenerHandle Listener;
};

USTRUCT()
struct FAbilityHandleArray
{
	GENERATED_BODY()
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
};

USTRUCT(BlueprintType)
struct FCustomMessage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> Owner;
	UPROPERTY(BlueprintReadWrite)
	int32 CustomInt;
	UPROPERTY(BlueprintReadWrite)
	float CustomFloat;
	UPROPERTY(BlueprintReadWrite)
	FVector CustomVector;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PCG1_API UAbilityManagerComponent : public UActorComponent, public IInputBindable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManagerComponent();

	UFUNCTION(BlueprintCallable, Category="AbilityManager")
	void AddAbilities(UPlayerAbilitySet* AbilitySet);
	UFUNCTION(BlueprintCallable, Category="AbilityManager")
	void RemoveAbilities(UPlayerAbilitySet* AbilitySet);

	UFUNCTION(BlueprintCallable, Category="AbilityManager")
	void AddAbility(FGameplayTag tag, UGameplayAbility* Ability);
	UFUNCTION(BlueprintCallable, Category="AbilityManager")
	void RemoveAbility(FGameplayTag tag);

	
	virtual void SetupInput_Implementation(UEnhancedInputComponent* InputComponent) override;

protected:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInput;
	UPROPERTY()
	UAbilitySystemComponent* ASC;
	UPROPERTY()
	TMap<FGameplayTag, FAbilitySubscriptionData> GameplayAbilitiesMap;

	UPROPERTY()
	TMap<UPlayerAbilitySet*, FAbilityHandleArray> AbilityHandles;
	
	virtual void BeginPlay() override;
	
	void OnAbilityTagMessage(FGameplayTag tag, const FCustomMessage& message);
};
