// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleEventManager.h"
DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog); 


// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	
	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	//RootComponent = TankBody;
	TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm -> SetupAttachment(TankBody);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	CannonSpawnPoint = CreateDefaultSubobject<UArrowComponent>("CannonSpawnPoint");
	CannonSpawnPoint->SetupAttachment(TankTurret);
}

void ATankPawn::MoveForward(float Scale)
{
	ForwardScale = Scale;
}
void ATankPawn::MoveRight(float Scale)
{
	RightScale = Scale;
}
void ATankPawn::RotateRight(float Scale)
{
	RotateScale = Scale;
}

void ATankPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	TankController = Cast<ATankPlayerController>(NewController);
}

void ATankPawn::Fire()
{
	if(Cannon)
		Cannon->Fire(projectileAmmo, traceAmmo, bulletsAmmo);
	else if(Cannon2)
		Cannon2->Fire(projectileAmmo, traceAmmo, bulletsAmmo);
}

void ATankPawn::FireSpecial()
{
	if(Cannon)
		Cannon->FireSpecial(projectileAmmo, traceAmmo, bulletsAmmo);
	else if(Cannon2)
		Cannon2->FireSpecial(projectileAmmo, traceAmmo, bulletsAmmo);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> InCannonClass) 
{
	if(!Cannon && !Cannon2)
	{
		CannonClass = InCannonClass;
		if(CannonClass)
		{
			auto CannonPos = CannonSpawnPoint->GetComponentTransform();
			FActorSpawnParameters Parameters;
			Parameters.Instigator = this;
			Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPos, Parameters);
			Cannon->AttachToComponent(CannonSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
	else if(Cannon && !Cannon2)
	{
		CannonClass = InCannonClass;
		if(CannonClass)
		{
			auto CannonPos = CannonSpawnPoint->GetComponentTransform();
			FActorSpawnParameters Parameters;
			Parameters.Instigator = this;
			Cannon2 = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPos, Parameters);
			Cannon2->AttachToComponent(CannonSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
	else if(Cannon && Cannon2)
	{
		Cannon->Destroy();
		Cannon = nullptr;
		
		CannonClass = InCannonClass;
		if(CannonClass)
		{
			auto CannonPos = CannonSpawnPoint->GetComponentTransform();
			FActorSpawnParameters Parameters;
			Parameters.Instigator = this;
			Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPos, Parameters);
			Cannon->AttachToComponent(CannonSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

void ATankPawn::ChangeCannon()
{
	if(Cannon && Cannon2) 
	{
		Cannon->SetActorHiddenInGame(true); 
		Swap(Cannon, Cannon2);
		Cannon->SetActorHiddenInGame(false); 
	
	}
}

void ATankPawn::AddBulletsProj(int bullets)
{
	projectileAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), projectileAmmo));
}
void ATankPawn::AddBulletsTrace(int bullets)
{
	traceAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));
}
void ATankPawn::AddBulletsGun(int bullets)
{
	bulletsAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), bulletsAmmo));
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);
}

void ATankPawn::Destroyed()
{
	Super::Destroyed();
	if(Cannon)
		Cannon->Destroy();
	if(Cannon2)
		Cannon2->Destroy();
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// moving
	CurrentForwardScale = FMath::Lerp(CurrentForwardScale, ForwardScale, InterpolationKey);
	auto CurrentLocation = GetActorLocation();
	auto ForwardVector = GetActorForwardVector();
	auto RightVector = GetActorRightVector();
	auto movePosition = CurrentLocation + ForwardVector * CurrentForwardScale * MovementSpeed * DeltaTime + RightVector * RightScale * MovementSpeed * DeltaTime;
	SetActorLocation(movePosition, true);

	// rotating tank
	CurrentRotateScale = FMath::Lerp(CurrentRotateScale, RotateScale, InterpolationKey);
	UE_LOG(TankLog, Warning, TEXT("CorrentRotateScale = %f RotateScale = %f"), CurrentRotateScale, RotateScale);
	float yawRotation = RotationSpeed * CurrentRotateScale * DeltaTime;
	auto currentRotation = GetActorRotation();
	yawRotation = currentRotation.Yaw + yawRotation;
	auto newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	// rotating turret
	if(TankController)
	{
		FVector mousePosition = TankController->GetMousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePosition);
		FRotator currentTurRotation = TankTurret->GetComponentRotation();
		targetRotation.Pitch = currentTurRotation.Pitch;
		targetRotation.Roll = currentTurRotation.Roll;
		TankTurret->SetWorldRotation(FMath::Lerp(currentTurRotation, targetRotation, TurretRotationInterpolationKey));
	}
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

