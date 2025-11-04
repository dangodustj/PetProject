// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputComponent.h"

#include "AbilitySystemInterface.h"


// Sets default values for this component's properties
UPlayerInputComponent::UPlayerInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		if (IAbilitySystemInterface *AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwner()))
		{
			ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		}
	}
	
}

void UPlayerInputComponent::CallAbilityInputPressed(const EInputActionID InputID) const
{
	if (ASC)
	{
		ASC->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
}

void UPlayerInputComponent::CallAbilityInputReleased(const EInputActionID InputID) const
{
	if (ASC)
	{
		ASC->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}


void UPlayerInputComponent::SetupInput_Implementation(UEnhancedInputComponent* InputComponent)
{
	EnhancedInput = InputComponent;
	EnhancedInput->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnLook);

	EnhancedInput->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnMove);
	EnhancedInput->BindAction(JumpInputAction, ETriggerEvent::Started, this, &UPlayerInputComponent::OnJump);
	EnhancedInput->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &UPlayerInputComponent::OnJumpReleased);
	EnhancedInput->BindAction(LMBInputAction, ETriggerEvent::Started, this, &UPlayerInputComponent::OnLMB);
	EnhancedInput->BindAction(LMBInputAction, ETriggerEvent::Completed, this, &UPlayerInputComponent::OnLMBReleased);
	EnhancedInput->BindAction(RMBInputAction, ETriggerEvent::Started, this, &UPlayerInputComponent::OnRMB);
	EnhancedInput->BindAction(RMBInputAction, ETriggerEvent::Completed, this, &UPlayerInputComponent::OnRMBReleased);
	EnhancedInput->BindAction(DashInputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnDash);
	EnhancedInput->BindAction(SprintInputAction, ETriggerEvent::Started, this, &UPlayerInputComponent::OnSprint);
	EnhancedInput->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &UPlayerInputComponent::OnSprintReleased);
	EnhancedInput->BindAction(Action1InputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnAction1);
	EnhancedInput->BindAction(Action2InputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnAction2);
	EnhancedInput->BindAction(Action3InputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnAction3);
	EnhancedInput->BindAction(Action4InputAction, ETriggerEvent::Triggered, this, &UPlayerInputComponent::OnAction4);
	
}

void UPlayerInputComponent::OnMove(const FInputActionValue& Value)
{
	OnMoveTriggered.Broadcast(Value);
}

void UPlayerInputComponent::OnLook(const FInputActionValue& Value) 
{
	OnLookTriggered.Broadcast(Value);
}

void UPlayerInputComponent::OnJump(const FInputActionValue& Value) 
{
	OnJumpTriggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Jump);
}
void UPlayerInputComponent::OnJumpReleased(const FInputActionValue& Value) 
{
	OnJumpReleasedTriggered.Broadcast(Value);
	CallAbilityInputReleased(EInputActionID::Jump);
}

void UPlayerInputComponent::OnLMB(const FInputActionValue& Value) 
{
	OnLMBTriggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::LMB);
}

void UPlayerInputComponent::OnLMBReleased(const FInputActionValue& Value) 
{
	OnLMBReleasedTriggered.Broadcast(Value);
	CallAbilityInputReleased(EInputActionID::LMB);
}

void UPlayerInputComponent::OnRMB(const FInputActionValue& Value) 
{
	OnRMBTriggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::RMB);
}
void UPlayerInputComponent::OnRMBReleased(const FInputActionValue& Value) 
{
	OnRMBReleasedTriggered.Broadcast(Value);
	CallAbilityInputReleased(EInputActionID::RMB);
}

void UPlayerInputComponent::OnDash(const FInputActionValue& Value) 
{
	OnDashTriggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Dash);
}

void UPlayerInputComponent::OnSprint(const FInputActionValue& Value)
{
	OnSprintTriggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Sprint);
}

void UPlayerInputComponent::OnSprintReleased(const FInputActionValue& Value)
{
	OnSprintReleasedTriggered.Broadcast(Value);
	CallAbilityInputReleased(EInputActionID::Sprint);
}

void UPlayerInputComponent::OnAction1(const FInputActionValue& Value) 
{
	OnAction1Triggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Action1);
}

void UPlayerInputComponent::OnAction2(const FInputActionValue& Value) 
{
	OnAction2Triggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Action2);
}

void UPlayerInputComponent::OnAction3(const FInputActionValue& Value) 
{
	OnAction3Triggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Action3);
}

void UPlayerInputComponent::OnAction4(const FInputActionValue& Value) 
{
	OnAction4Triggered.Broadcast(Value);
	CallAbilityInputPressed(EInputActionID::Action4);
}




