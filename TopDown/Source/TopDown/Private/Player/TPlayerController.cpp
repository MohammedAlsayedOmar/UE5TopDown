// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Components/TDebugComponent.h"
#include "Player/TCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMath.h"

ATPlayerController::ATPlayerController()
{
    SetShowMouseCursor(true);
}

void ATPlayerController::OnPossess(APawn *NewPawn)
{
    Super::OnPossess(NewPawn);
    PossessedCharacter = Cast<ATCharacter>(NewPawn);

    SetupInputs();

    UTDebugComponent *DebugComp = Cast<UTDebugComponent>(PossessedCharacter->GetComponentByClass(UTDebugComponent::StaticClass()));
    if (DebugComp)
    {
        DebugComp->OnPlayerControllerInitialized(this);
    }
}

void ATPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->ClearActionEventBindings();
        EnhancedInputComponent->ClearActionValueBindings();
        EnhancedInputComponent->ClearDebugKeyBindings();

        BindActions(DefaultInputMappingContext);
        BindActions(DebugInputMappingContext);
    }
    else
    {
        UE_LOG(LogTemp, Fatal, TEXT("ALS Community requires Enhanced Input System to be activated in project settings to function properly"));
    }
}

void ATPlayerController::BindActions(UInputMappingContext *Context)
{
    if (Context == nullptr)
        return;

    UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInputComponent == nullptr)
        return;

    // There may be more than one keymapping assigned to one action. So, first filter duplicate action entries to prevent multiple delegate bindings
    const TArray<FEnhancedActionKeyMapping> &Mappings = Context->GetMappings();
    TSet<const UInputAction *> UniqueActions;
    for (const FEnhancedActionKeyMapping &Keymapping : Mappings)
    {
        UniqueActions.Add(Keymapping.Action);
    }
    for (const UInputAction *UniqueAction : UniqueActions)
    {
        EnhancedInputComponent->BindAction(UniqueAction, ETriggerEvent::Triggered, Cast<UObject>(this), UniqueAction->GetFName());
    }
}

void ATPlayerController::SetupInputs()
{
    if (PossessedCharacter == nullptr)
        return;

    if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        FModifyContextOptions Options;
        Options.bForceImmediately = 1;
        Subsystem->AddMappingContext(DefaultInputMappingContext, 1, Options);
        UTDebugComponent *DebugComp = Cast<UTDebugComponent>(PossessedCharacter->GetComponentByClass(UTDebugComponent::StaticClass()));
        if (DebugComp)
        {
            // Do only if we have debug component
            Subsystem->AddMappingContext(DebugInputMappingContext, 0, Options);
        }
    }
}

void ATPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    float mouseX;
    float mouseY;
    if (!GetMousePosition(mouseX, mouseY)) return;

    // if (FGenericPlatformMath::IsNaN(mouseX) || FGenericPlatformMath::IsNaN(mouseY)) {return; }

    int32 sizeX, sizeY;
    GetViewportSize(sizeX, sizeY);
    AimDirection.X = FMath::GetMappedRangeValueClamped(FVector2D(.0f, sizeX), FVector2D(-1.0f, 1.0f), mouseX);
    AimDirection.Y = FMath::GetMappedRangeValueClamped(FVector2D(.0f, sizeY), FVector2D(1.0f, -1.0f), mouseY);

    // UE_LOG(LogTemp, Log, TEXT("ViewportSize: %i, %i"), sizeX, sizeY);
    // UE_LOG(LogTemp, Log, TEXT("Mouse Location: %f, %f"), mouseX, mouseY);
    // UE_LOG(LogTemp, Log, TEXT("AimDirection: %f, %f"), AimDirection.X, AimDirection.Y);
}

void ATPlayerController::ForwardMovementAction(const FInputActionValue &Value)
{
    if (PossessedCharacter == nullptr)
        return;

    PossessedCharacter->ForwardMovementAction(Value.GetMagnitude());
}

void ATPlayerController::RightMovementAction(const FInputActionValue &Value)
{
    if (PossessedCharacter == nullptr)
        return;

    PossessedCharacter->RightMovementAction(Value.GetMagnitude());
}

void ATPlayerController::ShootAction(const FInputActionValue &Value)
{
    if (PossessedCharacter == nullptr)
        return;

    PossessedCharacter->ShootAction(Value.Get<bool>());
}

void ATPlayerController::DebugToggleTracesAction(const FInputActionValue &Value)
{
    if (PossessedCharacter && Value.Get<bool>())
    {
        UTDebugComponent *DebugComp = Cast<UTDebugComponent>(PossessedCharacter->GetComponentByClass(UTDebugComponent::StaticClass()));
        if (DebugComp)
        {
            DebugComp->ToggleTraces();
        }
    }
}