// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    UTWeaponComponent();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void EquipWeapon(class UTWeaponDataAsset* NewWeapon);

    UFUNCTION(BlueprintCallable)
    void Shoot(bool bShooting);

private:
    float LastShootTime;
    bool bIsShooting;

public:	
    UPROPERTY(Category = "Weapon", BlueprintReadOnly)
	TObjectPtr<class ATCharacter> OwnerCharacter;

protected:
    TWeakObjectPtr<class UTWeaponDataAsset> CurrentSelectedWeapon;

};