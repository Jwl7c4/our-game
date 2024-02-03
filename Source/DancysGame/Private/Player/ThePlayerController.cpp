// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ThePlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Character/DancysGameCharacter.h"

AThePlayerController::AThePlayerController()
{
	PossessedPawn = nullptr;
}

void AThePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PossessedPawn = Cast<ADancysGameCharacter>(GetPawn());
}



void AThePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AThePlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AThePlayerController::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThePlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThePlayerController::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AThePlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2Do
	FVector2D MovementVector = Value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	PossessedPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	PossessedPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void AThePlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();


	// add yaw and pitch input to controller
	PossessedPawn->AddControllerYawInput(LookAxisVector.X);
	PossessedPawn->AddControllerPitchInput(LookAxisVector.Y);
}

void AThePlayerController::Jump()
{
	PossessedPawn->Jump();
}

void AThePlayerController::StopJumping()
{
	PossessedPawn->StopJumping();
}

//void AThePlayerController::OnPossess(APawn* aPawn)
//{
//}
//
//void AThePlayerController::OnUnPossess()
//{
//}
