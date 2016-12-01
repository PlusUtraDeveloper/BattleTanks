// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "AimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MJPOGI: BeginPlay"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	//auto ControlledTank = GetPawn();
	if (ensure(PlayerTank))
	{
		// Move Towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
	
		// Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		// Fire when ready
		AimingComponent->Fire();
	}
}




