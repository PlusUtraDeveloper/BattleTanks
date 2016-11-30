// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333f;


	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	void AimAtCrossHair();

	bool GetCrossHairRayHitLocation(FVector&) const;

	bool GetLookDirection(FVector2D, FVector&) const;

	bool GetLookVectorHitLocation(FVector, FVector&) const;
	
	
};
