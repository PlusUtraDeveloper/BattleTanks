// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
private:
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrel(FVector AimDirection);
};
