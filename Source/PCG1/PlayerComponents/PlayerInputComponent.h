// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InputBindable.h"
#include "PlayerInputComponent.generated.h"

UENUM()
enum class EInputActionID : uint8
{
	None, Jump, LMB, RMB, Dash, Sprint, Action1, Action2, Action3, Action4
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionTriggered, const FInputActionValue&, ActionValue);

UCLASS(ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class PCG1_API UPlayerInputComponent : public UActorComponent, public IInputBindable
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* MoveInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* LookInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* JumpInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* LMBInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* RMBInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* DashInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* SprintInputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* Action1InputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* Action2InputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* Action3InputAction;
	UPROPERTY(EditAnywhere, Category = InputActions)
	UInputAction* Action4InputAction;
	
protected:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInput;
	UPROPERTY()
	UAbilitySystemComponent* ASC;

public:
	// Sets default values for this component's properties
	UPlayerInputComponent();

	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnMoveTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnLookTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnJumpTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnJumpReleasedTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnLMBTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnLMBReleasedTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnRMBTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnRMBReleasedTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnDashTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnSprintTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnSprintReleasedTriggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnAction1Triggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnAction2Triggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnAction3Triggered;
	UPROPERTY(BlueprintAssignable)
	FOnActionTriggered OnAction4Triggered;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CallAbilityInputPressed(const EInputActionID InputID) const;
	void CallAbilityInputReleased(const EInputActionID InputID) const;
	
public:

	virtual void SetupInput_Implementation(UEnhancedInputComponent* InputComponent) override;
	UFUNCTION()
	void OnMove(const FInputActionValue& Value);
	UFUNCTION()
	void OnLook(const FInputActionValue& Value);
	UFUNCTION()
	void OnJump(const FInputActionValue& Value);
	UFUNCTION()
	void OnJumpReleased(const FInputActionValue& Value);
	UFUNCTION()
	void OnLMB(const FInputActionValue& Value);
	UFUNCTION()
	void OnLMBReleased(const FInputActionValue& Value);
	UFUNCTION()
	void OnRMB(const FInputActionValue& Value);
	UFUNCTION()
	void OnRMBReleased(const FInputActionValue& Value);
	UFUNCTION()
	void OnDash(const FInputActionValue& Value);
	UFUNCTION()
	void OnSprint(const FInputActionValue& Value);
	UFUNCTION()
	void OnSprintReleased(const FInputActionValue& Value);
	UFUNCTION()
	void OnAction1(const FInputActionValue& Value); 
	UFUNCTION()
	void OnAction2(const FInputActionValue& Value);
	UFUNCTION()
	void OnAction3(const FInputActionValue& Value);
	UFUNCTION()
	void OnAction4(const FInputActionValue& Value);
};
