// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "ThePlayerController.generated.h"

struct FInputActionValue;

UCLASS()
class DANCYSGAME_API AThePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AThePlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	virtual void SetupInputComponent() override;

	//UFUNCTION(BlueprintCallable)
	//virtual void OnPossess(APawn* aPawn) override;

	//UFUNCTION(BlueprintCallable)
	//virtual void OnUnPossess() override;

	// To add mapping context
	virtual void BeginPlay();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Jump();

	void StopJumping();

private:
	class ADancysGameCharacter* PossessedPawn;
};
