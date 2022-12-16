//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponSystem/DataAsset/WeaponTypes/TWeaponTypeBase.h"
#include "TWeaponRanged.generated.h"
 
/**
 * 
 */
UCLASS()
class TOPDOWN_API UTWeaponRanged : public UTWeaponTypeBase
{
	GENERATED_BODY()

public:
    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    bool bTravellingProjectile;

    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    bool bFollowTarget;

    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    float Range;

    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    float RandomSpreadAngle = 0.0f;

    UPROPERTY(Category="Weapon", EditDefaultsOnly)
    int32 NumberOfBulletsInShot = 1;

    UPROPERTY(Category="Weapon", EditDefaultsOnly, meta = (EditCondition = "bTravellingProjectile", EditConditionHides))
    float ProjectileSpeed;

    UPROPERTY(Category="Weapon", EditDefaultsOnly, meta = (EditCondition = "bTravellingProjectile", EditConditionHides))
    TSubclassOf<AActor> ProjectileActor;



    void Shoot(class ATCharacter* character) override;
};