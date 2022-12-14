// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS(BluePrintType)
class TOPDOWN_API UTWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category="Weapon", EditDefaultsOnly)
	TObjectPtr<AActor> WeaponActor;

	UPROPERTY(Category="Weapon", EditDefaultsOnly)
	FName AttachedBoneName;

	UPROPERTY(Category="Weapon", EditDefaultsOnly)
	float CooldownSeconds;

	UPROPERTY(Category="Weapon", EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(Category="Weapon", EditDefaultsOnly)
	//TSubclassOf<class UTWeaponTypeBase> WeaponType;
	TObjectPtr<class UTWeaponTypeBase> WeaponType;
};
