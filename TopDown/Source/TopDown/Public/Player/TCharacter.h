// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"

UCLASS()
class TOPDOWN_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	/** Input */

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TopDown|Input")
	void ForwardMovementAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TopDown|Input")
	void RightMovementAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TopDown|Input")
	void ShootAction(bool Value);

protected:
	UPROPERTY(Category = "Player", EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(Category = "Player", EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(Category = "Player | Weapon", EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UTWeaponDataAsset> TestWeapon;
};
