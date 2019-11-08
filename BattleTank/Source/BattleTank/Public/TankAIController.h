// okay....

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	void AimAt();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
