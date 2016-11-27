// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerController();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find Player Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank found: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetControlledTank())
	{
		// Move Towards player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerController()->GetActorLocation());
		
		// Fire when ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerController() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	else { return Cast<ATank>(PlayerPawn); }
}



