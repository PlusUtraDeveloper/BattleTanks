// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"
#include "AimingComponent.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAimingComponent::BeginPlay()
{
	// So that first first is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	if (!ensure(BarrelToSet) || !ensure(TurrentToSet)) { return; }
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (Ammo <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
}

void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate Launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace	
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel();
	}

}

void UAimingComponent::MoveBarrel()
{
	// Work-out difference between current Barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	if(FMath::Abs(DeltaRotator.Yaw) < 180)		
	{
		Turrent->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turrent->Rotate(-DeltaRotator.Yaw);
	}
}

void UAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammo--;
	}
}


int UAimingComponent::GetAmmoCount() const
{
	return Ammo;
}