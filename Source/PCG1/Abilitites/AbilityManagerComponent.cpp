// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilitites/AbilityManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"

// Sets default values for this component's properties
UAbilityManagerComponent::UAbilityManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface *AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwner());
		if (AbilitySystemInterface)
		{
			ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		}
	}
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability System component not found"));
	}

	
}

void UAbilityManagerComponent::SetupInput_Implementation(UEnhancedInputComponent* InputComponent)
{
	if (InputComponent)
	{
		EnhancedInput = InputComponent;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component not found"));
	}
}

void UAbilityManagerComponent::AddAbilities(UPlayerAbilitySet* AbilitySet)
{
	if (AbilityHandles.Contains(AbilitySet))
	{
		return;
	}

	AbilityHandles.Add(AbilitySet);
	FAbilityHandleArray AbilitiesArray;
	for (const FPlayerAbilityData& data: AbilitySet->Abilities)
	{
		if (ASC && data.Ability)
		{
			FGameplayAbilitySpec spec(data.Ability, 1 ,static_cast<int32>(data.InputID), GetOwner());
			FGameplayAbilitySpecHandle handle = ASC->GiveAbility(spec);
			FGameplayAbilitySpec* bSpec = ASC->FindAbilitySpecFromHandle(handle);
			AbilitiesArray.AbilitySpecs.Add(bSpec);
		}
	}
	AbilityHandles[AbilitySet] = AbilitiesArray;
}

void UAbilityManagerComponent::RemoveAbilities(UPlayerAbilitySet* AbilitySet)
{
	for (auto spec : AbilityHandles[AbilitySet].AbilitySpecs)
	{
		ASC->ClearAbility(spec->Handle);
	}
	AbilityHandles.Remove(AbilitySet);
}


void UAbilityManagerComponent::AddAbility(FGameplayTag tag, UGameplayAbility* Ability)
{
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability System Component does not exist"));
		return;
	}
	if (GameplayAbilitiesMap.Contains(tag))
	{
		UE_LOG(LogTemp, Error, TEXT("Ability already exist"));
		return;
	}
	FGameplayAbilitySpec spec(Ability, 1 ,INDEX_NONE, GetOwner());
	FGameplayAbilitySpecHandle handle = ASC->GiveAbility(spec);


	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	
	auto Listener = MessageSubsystem.RegisterListener<FCustomMessage>(tag, this, &UAbilityManagerComponent::OnAbilityTagMessage);
	
	GameplayAbilitiesMap.Add(tag, { spec, Listener	});

}

void UAbilityManagerComponent::RemoveAbility(FGameplayTag tag)
{
	if (!ASC) return;
	if (!GameplayAbilitiesMap.Contains(tag)) return;
	ASC->ClearAbility(GameplayAbilitiesMap[tag].AbilitySpec.Handle);
	UGameplayMessageSubsystem::Get(this).UnregisterListener(GameplayAbilitiesMap[tag].Listener);
	GameplayAbilitiesMap.Remove(tag);
}


void UAbilityManagerComponent::OnAbilityTagMessage(FGameplayTag tag, const FCustomMessage& message)
{
	if (message.Owner != GetOwner()) return;
	if (ASC && GameplayAbilitiesMap.Contains(tag))
	{
		ASC->TryActivateAbility(GameplayAbilitiesMap[tag].AbilitySpec.Handle);	
	}
}





