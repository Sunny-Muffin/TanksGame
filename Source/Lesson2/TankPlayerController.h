// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "TankPawn.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class LESSON2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void OnMoveForward(float Scale);
	void OnMoveRight(float Scale);
	void OnRotateRight(float Scale);

	void OnFire();
	void OnFireSpecial();
	void OnChangeCannon();
	
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePos() const {return MousePos;}

protected:
	UPROPERTY()
	ATankPawn* TankPawn;
	UPROPERTY()
	FVector MousePos;

};
