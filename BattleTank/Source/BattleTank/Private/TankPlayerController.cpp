// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"


int count = 0;
//On Tick
	// Call our Super class Tick()
	// AimTowardsCrosshair()


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not possessing tank"));
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }

	// Get world location of LineTrace through crosshair
	// If it hits the landscape
		// Tell controlled Tank to aim at this point 
	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) // Has side effect, is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);

	// Get the actor that the line trace is intersecting with during this hit event
		// AActor (the actor that was intersected)
	// Get the location of this actor
		// HitLocation = (location of this actor)
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	FVector StartLocation;
	FVector EndLocation;

	//Find Crosshair position
	//auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	auto ScreenLocation = GetScreenLocation();

	// "Deproject" screen position of cursor/crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {// Set LookDirection here
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//Linetrace along that LookDirection see what we hit(up to max range)
	return true; /*&HitLocation;  Return the hit location here*/
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation;
	FVector WorldDirection;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}
}

FVector2D ATankPlayerController::GetScreenLocation() const
{
	//Find Screen Location
	int32 ViewportSizeX, ViewportSizeY; // size of current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	return ScreenLocation;
}