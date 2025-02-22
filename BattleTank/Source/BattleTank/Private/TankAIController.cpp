// okay....


#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetControlledTank();
	if (!PlayerTank) {

		UE_LOG(LogTemp, Warning, TEXT("Cannot find player tank"));
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

void  ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimAt();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimAt()
{
	auto PlayerTank = GetPlayerTank();
	auto PlayerLocation = PlayerTank->GetActorLocation();
	GetControlledTank()->AimAt(PlayerLocation);
	
}