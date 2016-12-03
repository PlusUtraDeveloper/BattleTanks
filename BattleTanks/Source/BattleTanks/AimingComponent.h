// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming, 
	Reloading,
	NoAmmo
};

class AProjectile;
class UTankBarrel;
class UTankTurrent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int GetAmmoCount() const;

	EFiringState GetFiringState() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UAimingComponent();
	
	double LastFireTime = 0;
	FVector AimDirection;

	UTankTurrent* Turrent = nullptr;
	UTankBarrel* Barrel = nullptr;
		
	void MoveBarrel();
	bool IsBarrelMoving();

	virtual void BeginPlay() override;
	virtual void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int Ammo = 3;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	
	

};
