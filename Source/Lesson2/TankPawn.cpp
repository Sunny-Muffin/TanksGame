// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	//RootComponent = Collision;
	
	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	RootComponent = TankBody;
	//TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm -> SetupAttachment(TankBody);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera -> SetupAttachment(SpringArm);
}

void ATankPawn::MoveForward(float Scale)
{
	ForwardScale = Scale;
}
void ATankPawn::MoveRight(float Scale)
{
	RightScale = Scale;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ForwardScaleCurrent = FMath::Lerp(ForwardScaleCurrent, ForwardScaleMax, 0.1f);
	
	auto CurrentLocation = GetActorLocation();
	
	// moving
	auto ForwardVector = GetActorForwardVector();
	auto RightVector = GetActorRightVector();
	auto movePosition = CurrentLocation + ForwardVector * ForwardScale * MovementSpeed * DeltaTime + RightVector * RightScale * MovementSpeed * DeltaTime;
	SetActorLocation(movePosition, true);

	//FMath::Lerp(RotateScaleCurrent)
	
	auto Rotation = GetActorRotation();
	//Rotation.Yaw = Rotation.Yaw + RotationSpeed * RotateScale * DeltaTime;
	SetActorRotation(Rotation);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

