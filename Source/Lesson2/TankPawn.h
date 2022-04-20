// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"


UCLASS()
class LESSON2_API ATankPawn : public APawn
{
	GENERATED_BODY()


	

public:
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	//UBoxComponent* Collision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TankBody;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TankTurret;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float InterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float TurretRotationInterpolationKey = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Guns")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Guns")
	ACannon* Cannon;
	
	// Sets default values for this pawn's properties
	ATankPawn();

	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RotateRight(float Scale);

	virtual void PossessedBy(AController* NewController) override;

	void Fire();
	void FireSpecial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float ForwardScale = 0;
	float CurrentForwardScale = 0;
	float RightScale = 0;
	float RotateScale = 0;
	float CurrentRotateScale = 0;

	class ATankPlayerController* TankController;
};
