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
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	ATankPawn* TankPawn;

};
