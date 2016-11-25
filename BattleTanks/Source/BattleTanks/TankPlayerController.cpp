// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto MyTank = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"),*MyTank->GetName() );
}
ATank* ATankPlayerController::GetControlledTank() const
{ 
	return Cast<ATank>(GetPawn());
}



