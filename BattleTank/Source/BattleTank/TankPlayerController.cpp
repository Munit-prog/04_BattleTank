// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Miss ControlledTank "));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing:  %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
 }


ATank* ATankPlayerController::GetControlledTank() const
{
     return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation; //Out parameter
    if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
    {
       // UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());

          //TODO Tell controlled tank to aim at this point
    }
}

//Get world location if linetrace through crosshair, true If it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    //Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
  
    //"De-Project" the screen position of the crosshair to a world direction
    FVector WorldDirection;
    if (GetLookDirection(ScreenLocation, WorldDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *WorldDirection.ToString());
    }
    //Line-trace along that look direction, and see what we hit (up to max range)
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; //To be discarded
    return DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}