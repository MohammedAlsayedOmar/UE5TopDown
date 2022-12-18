// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TDebugComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UTDebugComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTDebugComponent();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TopDown|Debug")
	void OnPlayerControllerInitialized(APlayerController* Controller);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	UFUNCTION(BlueprintCallable, Category = "TopDown|Debug")
	void ToggleGlobalTimeDilationLocal(float TimeDilation);

	UFUNCTION(BlueprintCallable, Category = "TopDown|Debug")
	void ToggleSlomo();

	UFUNCTION(BlueprintCallable, Category = "TopDown|Debug")
	void ToggleTraces() { bShowTraces = !bShowTraces; }

	UFUNCTION(BlueprintCallable, Category = "TopDown|Debug")
	bool GetShowTraces() { return bShowTraces; }

	// utility functions to draw trace debug shapes,
	// which are derived from Engine/Private/KismetTraceUtils.h.
	// Sadly the functions are private, which was the reason
	// why there reimplemented here.
	static void DrawDebugLineTraceSingle(const UWorld* World,
	                                     const FVector& Start,
	                                     const FVector& End,
	                                     EDrawDebugTrace::Type DrawDebugType,
	                                     bool bHit,
	                                     const FHitResult& OutHit,
	                                     FLinearColor TraceColor,
	                                     FLinearColor TraceHitColor,
	                                     float DrawTime);

	static void DrawDebugCapsuleTraceSingle(const UWorld* World,
											const FVector& Start,
											const FVector& End,
											const FCollisionShape& CollisionShape,
											EDrawDebugTrace::Type DrawDebugType,
											bool bHit,
											const FHitResult& OutHit,
											FLinearColor TraceColor,
											FLinearColor TraceHitColor,
											float DrawTime);

	static void DrawDebugSphereTraceSingle(const UWorld* World,
	                                       const FVector& Start,
	                                       const FVector& End,
	                                       const FCollisionShape& CollisionShape,
	                                       EDrawDebugTrace::Type DrawDebugType,
	                                       bool bHit,
	                                       const FHitResult& OutHit,
	                                       FLinearColor TraceColor,
	                                       FLinearColor TraceHitColor,
	                                       float DrawTime);

	static void DrawDebugSphereShape(const UWorld* World,
								const FVector& Center,
								const float Radius,
								EDrawDebugTrace::Type DrawDebugType,
								bool bHit,
								FColor TraceColor,
								FColor TraceHitColor,
								float DrawTime);

public:
	UPROPERTY(BlueprintReadOnly, Category = "TopDown|Debug")
	TObjectPtr<class ATCharacter> OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDown|Debug")
	bool bSlomo = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TopDown|Debug")
	bool bShowHud = false;

private:
	static bool bShowTraces;

};
