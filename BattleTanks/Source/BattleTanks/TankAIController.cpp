// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "AimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (ensure(PlayerTank))
	{
		// Move Towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
	
		auto AimingComponent = ControlledTank->FindComponentByClass<UAimingComponent>();
		// Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		// Fire when ready
		AimingComponent->Fire();
	}
}




