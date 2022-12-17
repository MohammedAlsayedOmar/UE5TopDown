// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TAIController.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWN_API ATAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UPROPERTY(Category = "AI", EditDefaultsOnly)
	class UBehaviorTree *BTAsset;
};
