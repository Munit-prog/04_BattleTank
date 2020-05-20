// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "..\Public\TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Miss AIControlledTank "));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing:  %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerTank)
    {
        return nullptr;
    }
    return Cast<ATank>(PlayerTank);
}
