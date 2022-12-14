// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TWeaponTypeBase.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class TOPDOWN_API UTWeaponTypeBase : public UDataAsset
{
	GENERATED_BODY()
	    
public:
    UFUNCTION()
    virtual void Shoot(class ATCharacter* character);
};