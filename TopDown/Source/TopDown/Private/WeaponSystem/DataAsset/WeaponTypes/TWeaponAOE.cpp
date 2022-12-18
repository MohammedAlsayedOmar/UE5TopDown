// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSystem/DataAsset/WeaponTypes/TWeaponAOE.h"

#include "Player/TCharacter.h"
#include "Components/TDebugComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UTWeaponAOE::Shoot(class ATCharacter *character)
{
    UE_LOG(LogTemp, Log, TEXT("SHOOTING AOE"));

    UTDebugComponent *TDebugComponent = character->FindComponentByClass<UTDebugComponent>();

    const FVector &TraceStart = character->GetActorLocation();
    const FVector &TraceEnd = character->GetActorLocation() + character->GetMesh()->GetForwardVector() * Range;

    FHitResult HitResult;
    {
        UWorld *World = character->GetWorld();

        TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
        traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

        UClass *seekClass = ATCharacter::StaticClass();

        TArray<AActor *> ignoreActors;
        ignoreActors.Init(character, 1);

        TArray<AActor *> outActors;
        UKismetSystemLibrary::SphereOverlapActors(World, TraceStart, Range, traceObjectTypes, seekClass, ignoreActors, outActors);

        bool bHit = outActors.Num() > 0;

        for (AActor *overlappedActor : outActors)
        {
            UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());
        }

        if (TDebugComponent && TDebugComponent->GetShowTraces())
        {
            UTDebugComponent::DrawDebugSphereShape(World,
                                                   TraceStart,
                                                   Range,
                                                   EDrawDebugTrace::Type::ForDuration,
                                                   bHit,
                                                   FColor::Red,
                                                   FColor::Green,
                                                   2.0f);
        }
    }
}
