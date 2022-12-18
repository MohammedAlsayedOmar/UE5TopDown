// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TCharacter.h"
#include "Camera/CameraComponent.h"
#include "Player/TPlayerController.h"
#include "Components/TWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

ATCharacter::ATCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 2000.0f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATCharacter::BeginPlay()
{
	Super::BeginPlay();

	UTWeaponComponent *WeaponComp = Cast<UTWeaponComponent>(GetComponentByClass(UTWeaponComponent::StaticClass()));
	if (WeaponComp)
	{
		WeaponComp->EquipWeapon(TestWeapon.Get());
	}
}

void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/** Input */

void ATCharacter::LookAt_Implementation(FVector2D LookAtVector, float DeltaTime)
{
	float offsetSize = 400.0f; // Should be an exposed variable but that's for tomorrow's me >_<
	SpringArmComponent->SocketOffset = ClampVector(
		FMath::Lerp(
			SpringArmComponent->SocketOffset,
			FVector(.0f, LookAtVector.X * offsetSize, LookAtVector.Y * offsetSize),
			DeltaTime * 10.0f),
		FVector(.0f, -offsetSize, -offsetSize),
		FVector(.0f, offsetSize, offsetSize));

	GetMesh()->SetRelativeRotation(
		FRotator(
			.0f,
			FMath::RadiansToDegrees(FMath::Atan2(LookAtVector.X, LookAtVector.Y)),
			.0f));
}

void ATCharacter::ForwardMovementAction_Implementation(float Value)
{
	AddMovementInput(FVector(100.0f, .0f, .0f), Value);
}

void ATCharacter::RightMovementAction_Implementation(float Value)
{
	AddMovementInput(FVector(.0f, 100.0, .0f), Value);
}

void ATCharacter::ShootAction_Implementation(bool Value)
{
	UE_LOG(LogTemp, Log, TEXT("SHOOT_FROMPLAYERCHAR!"));
	UTWeaponComponent *WeaponComp = Cast<UTWeaponComponent>(GetComponentByClass(UTWeaponComponent::StaticClass()));
	if (WeaponComp)
	{
		WeaponComp->Shoot(Value);
	}
}
