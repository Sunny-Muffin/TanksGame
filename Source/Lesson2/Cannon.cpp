// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);
}

void ACannon::Fire()
{
	if(!bReadyToFire)
		return;
	
	switch (Type)
	{
	case ECannonType::Projectile:
		if(projectileAmmo > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Projectile")));
			projectileAmmo -= 1;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), projectileAmmo));
		}
		break;
	case ECannonType::Trace:
		if(traceAmmo > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Trace")));
			traceAmmo -= 1;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));
		}
		break;
	}
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, FireRate, false);
}

void ACannon::FireSpecial()
{
	if(!bReadyToFire)
		return;
	switch (Type)
	{
	case ECannonType::Projectile:
		if(projectileAmmo > 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileSpecial")));
			projectileAmmo -= 3;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), projectileAmmo));
		}
		break;
	case ECannonType::Trace:
		if(traceAmmo > 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceSpecial")));
			traceAmmo -= 3;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));
		}
		break;
	}
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, FireRate*3, false);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::OnReload()
{
	bReadyToFire = true;
}

