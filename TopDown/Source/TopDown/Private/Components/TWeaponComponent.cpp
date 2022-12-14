// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TWeaponComponent.h"

#include "Player/TCharacter.h"
#include "Engine/World.h"
#include "WeaponSystem/DataAsset/TWeaponDataAsset.h"
#include "WeaponSystem/DataAsset/WeaponTypes/TWeaponTypeBase.h"

UTWeaponComponent::UTWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ATCharacter>(GetOwner());
    LastShootTime = 0;
    bIsShooting = false;
}

void UTWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if (!bIsShooting) return;
    
    UWorld *World = GetWorld();
    check(World)

    if (
        LastShootTime > World->GetTimeSeconds() ||
        CurrentSelectedWeapon == nullptr ||
        CurrentSelectedWeapon->WeaponType == nullptr)
    { return;}

    CurrentSelectedWeapon->WeaponType->Shoot(OwnerCharacter);
}

void UTWeaponComponent::EquipWeapon(class UTWeaponDataAsset *NewWeapon)
{
    // @@TODO Do something to remove the old weapon first!
    CurrentSelectedWeapon = NewWeapon;
}

void UTWeaponComponent::Shoot(bool bShooting)
{
    bIsShooting = bShooting;
}
