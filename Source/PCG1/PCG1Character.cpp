// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG1Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PCG1.h"
#include "Algo/ForEach.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "GameplayAttributes/BaseAttributeSet.h"

APCG1Character::APCG1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UPCGAbilityComponent>(TEXT("AbilitySystemComponent"));

	MainAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("MainAttributes"));

	PlayerEquipment = CreateDefaultSubobject<UPlayerEquipment>(TEXT("PlayerEquipment"));

	AbilityManager = CreateDefaultSubobject<UAbilityManagerComponent>(TEXT("AbilityManager"));

	PlayerInput = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("PlayerInput"));
}

void APCG1Character::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerEquipment)
	{
		PlayerEquipment->OnWeaponEquiped.AddDynamic(this, &APCG1Character::OnWeaponEquiped);
		PlayerEquipment->OnWeaponUnequiped.AddDynamic(this, &APCG1Character::OnWeaponUnequiped);
	}

	if (DefaultAbilities && AbilityManager)
	{
		AbilityManager->AddAbilities(DefaultAbilities);
	}

	PlayerInput->OnMoveTriggered.AddDynamic(this, &APCG1Character::Move);
	PlayerInput->OnLookTriggered.AddDynamic(this, &APCG1Character::Look);
}


UAbilitySystemComponent* APCG1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APCG1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Set up action bindings
	if (EnhancedInputComponent)
	{
		Algo::ForEach(GetComponents(), [&](UActorComponent* Component)
		{
			if (Component && Component->GetClass()->ImplementsInterface(UInputBindable::StaticClass()))
			{
				IInputBindable::Execute_SetupInput(Component, EnhancedInputComponent);
			}
		});

		
	}
	else
	{
		UE_LOG(LogPCG1, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void APCG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetCharacterMovement()->IsMovingOnGround())
	{
		if (!AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("PlayerStates.InAir")))
		{
			AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("PlayerStates.InAir"));
		}
	}else
	{
		if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("PlayerStates.InAir")))
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("PlayerStates.InAir"));
		}
	}
}

void APCG1Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void APCG1Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APCG1Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APCG1Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APCG1Character::OnWeaponEquiped_Implementation(AWeaponBase* weapon)
{
	AbilityManager->AddAbilities(weapon->GetWeaponData());
}

void APCG1Character::OnWeaponUnequiped_Implementation(AWeaponBase* weapon)
{
	AbilityManager->RemoveAbilities(weapon->GetWeaponData());
}
