// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(BTAsset);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn != nullptr)
    {
        GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
    }
}