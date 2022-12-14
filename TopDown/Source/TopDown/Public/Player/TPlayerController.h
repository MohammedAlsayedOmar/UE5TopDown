// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWN_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATPlayerController();	

	virtual void OnPossess(APawn* NewPawn) override;

	virtual void SetupInputComponent() override;

	virtual void BindActions(class UInputMappingContext *Context);

protected:
	void SetupInputs();

	UFUNCTION()
	void ForwardMovementAction(const FInputActionValue& Value);

	UFUNCTION()
	void RightMovementAction(const FInputActionValue& Value);

	UFUNCTION()
	void ShootAction(const FInputActionValue& Value);

	// Debug actions
	UFUNCTION()
	void DebugToggleTracesAction(const FInputActionValue& Value);

private:
	FVector2D AimDirection;

public:
	FVector2D GetAimDirection() const {return AimDirection;}

	void PlayerTick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "TopDown")
	TObjectPtr<class ATCharacter> PossessedCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TopDown|Input")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TopDown|Input")
	TObjectPtr<UInputMappingContext> DebugInputMappingContext = nullptr;


};
