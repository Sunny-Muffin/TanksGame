// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#include "DrawDebugHelpers.h"
#include "TankPawn.h"

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Forward", this, &ATankPlayerController::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::OnMoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::OnRotateRight);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::OnFire);
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPlayerController::OnFireSpecial);

	InputComponent->BindAction("ChangeCannon", IE_Pressed, this, &ATankPlayerController::OnChangeCannon);
	
	SetShowMouseCursor(true);
}

void ATankPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::OnMoveForward(float Scale)
{
	if(TankPawn)
		TankPawn->MoveForward(Scale);
}

void ATankPlayerController::OnMoveRight(float Scale)
{
	if(TankPawn)
		TankPawn->MoveRight(Scale);
}

void ATankPlayerController::OnRotateRight(float Scale)
{
	if(TankPawn)
		TankPawn->RotateRight(Scale);
}

void ATankPlayerController::OnFire()
{
	if(TankPawn)
		TankPawn->Fire();
}

void ATankPlayerController::OnFireSpecial()
{
	if(TankPawn)
		TankPawn->FireSpecial();
}

void ATankPlayerController::OnChangeCannon()
{
	if(TankPawn)
		TankPawn->ChangeCannon();
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector mouseDirection; 
	FVector mousePosition; // on screen
	DeprojectMousePositionToWorld(mousePosition, mouseDirection);

	//DrawDebugLine(GetWorld(), mousePosition, mousePosition+mouseDirection*5000, FColor::Blue, false, 1, 0 ,5); // рисует линии из центра экрана к курсору

	FVector pawnPos = TankPawn->GetActorLocation();
	auto screenHeight = FMath::Abs(pawnPos.Z - mousePosition.Z);
	MousePos = mousePosition - screenHeight * mouseDirection/mouseDirection.Z;
	//DrawDebugSphere(GetWorld(),  MousePos, 20, 16, FColor::Blue, false, 3); // рисует сферы на поверхности там, где двигается курсор

	
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos = pawnPos + dir * 1000;
	//DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Blue, false, 0.1f, 0 ,5);
}
