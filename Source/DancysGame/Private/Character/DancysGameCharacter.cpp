// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/DancysGameCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/ThePlayerState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADancysGameCharacter

ADancysGameCharacter::ADancysGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Ability Systems
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	bIsArmed = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

}

//void ADancysGameCharacter::BeginPlay()
//{
//	// Call the base class  
//	Super::BeginPlay();
//}

bool ADancysGameCharacter::isArmed()
{
	return bIsArmed;
}

void ADancysGameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AThePlayerState* PlayerStateBase = GetPlayerState<AThePlayerState>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PlayerStateBase->GetAbilitySystemComponent());
		PlayerStateBase->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateBase, this);
		CharacterAttributeSet = PlayerStateBase->CharacterAttributeSet;
	}
}

void ADancysGameCharacter::OnRep_PlayerState()
{

	Super::OnRep_PlayerState();

	if (AbilitySystemComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("OnRep_PlayerState - ASC null"));
	}


	if (AThePlayerState* PlayerStateBase = GetPlayerState<AThePlayerState>())
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(PlayerStateBase->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new Actor.
		PlayerStateBase->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateBase, this);
		//AbilitySystemComponent->InitAbilityActorInfo(PlayerStateBase, this);
		CharacterAttributeSet = PlayerStateBase->CharacterAttributeSet;
	}
}

bool ADancysGameCharacter::EquipRifle_Validate()
{
	return true;
}

void ADancysGameCharacter::EquipRifle_Implementation()
{
	if (AbilitySystemComponent)
	{
		// Create an ability spec
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = EquipAbility;
		FGameplayAbilitySpec Spec(SpecDef, 1); // Set level to 1 or the desired level

		// todo - should this just be permanent?
		AbilitySystemComponent->GiveAbilityAndActivateOnce(Spec);

		// Remove the ability after activation (if needed)
		AbilitySystemComponent->ClearAbility(Spec.Handle);

		bIsArmed = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADancysGameCharacter::EquipRifle_Implementation - Can't Equip. Ability System Component Not Set"));
	}
}

bool ADancysGameCharacter::UnEquipRifle_Validate() {
	return true;
}

void ADancysGameCharacter::UnEquipRifle_Implementation()
{
	if (AbilitySystemComponent)
	{
		// Create an ability spec
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = UnEquipAbility;
		FGameplayAbilitySpec Spec(SpecDef, 1); // Set level to 1 or the desired level

		// todo - should this just be permanent?
		AbilitySystemComponent->GiveAbilityAndActivateOnce(Spec);

		// Remove the ability after activation (if needed)
		AbilitySystemComponent->ClearAbility(Spec.Handle);

		bIsArmed = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADancysGameCharacter::UnEquipRifle_Validate - Can't UnEquip. Ability System Component Not Set"));
	}
}
