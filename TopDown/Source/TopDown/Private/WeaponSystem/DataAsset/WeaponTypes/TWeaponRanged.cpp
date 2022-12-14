// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSystem/DataAsset/WeaponTypes/TWeaponRanged.h"

#include "Player/TCharacter.h"
#include "Components/TDebugComponent.h"

void UTWeaponRanged::Shoot(class ATCharacter *character)
{
    UE_LOG(LogTemp, Log, TEXT("SHOOTING RANGED"));

    UTDebugComponent* TDebugComponent = character->FindComponentByClass<UTDebugComponent>();

    const FVector &TraceStart = character->GetActorLocation();
    const FVector &TraceEnd = character->GetActorLocation() + character->GetMesh()->GetForwardVector() * 1000.0f;

    FHitResult HitResult;
    {
        UWorld* World = character->GetWorld();

        FCollisionQueryParams Params;
        Params.AddIgnoredActor(character);

        const bool bHit = World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                                          ECC_Visibility, Params);
        if (TDebugComponent)
        {
            UTDebugComponent::DrawDebugLineTraceSingle(World,
                                                       TraceStart,
                                                       TraceEnd,
                                                       EDrawDebugTrace::Type::ForDuration,
                                                       bHit,
                                                       HitResult,
                                                       FLinearColor::Red,
                                                       FLinearColor::Green,
                                                       2.0f);
        }
    }
}