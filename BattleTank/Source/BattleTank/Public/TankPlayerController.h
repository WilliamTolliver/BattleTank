 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	virtual void Tick(float DeltaTime) override;
	//virtual bool DeprojectScreenPositionToWorld(float ScreenX, float ScreenY, FVector &WorldLocation, FVector &WorldDirection);
	virtual void BeginPlay() override;
	//Start the tank moving the turret, so that a shot would fire at the crosshair.
	void AimTowardsCrosshair();

	// Crosshair location
	UPROPERTY(EditAnywhere, BlueprintReadWrite)float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)float CrosshairYLocation = 0.3333;

	// Return an OUT parameter, true if hit landscape

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
};
