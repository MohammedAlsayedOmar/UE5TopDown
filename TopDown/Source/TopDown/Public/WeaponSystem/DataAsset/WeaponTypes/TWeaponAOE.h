//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponSystem/DataAsset/WeaponTypes/TWeaponTypeBase.h"
#include "TWeaponAOE.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWN_API UTWeaponAOE : public UTWeaponTypeBase
{
	GENERATED_BODY()

public:
    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    float Range;

    void Shoot(class ATCharacter* character) override;
};