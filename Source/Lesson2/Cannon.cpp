// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "DrawDebugHelpers.h"



// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EmptyRoot = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = EmptyRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);
}

void ACannon::Fire(int& ammo1, int& ammo2, int& ammo3)
{
	if(!bReadyToFire)
		return;
	
	switch (Type)
	{
	case ECannonType::Projectile:
		{
			if(ammo1 > 0)
			{
				if(ProjectileType)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Projectile")));
					
					FActorSpawnParameters SpawnParameters;
					SpawnParameters.Instigator = GetInstigator();
					SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					GetWorld()->SpawnActor<AProjectile>(ProjectileType, SpawnPoint->GetComponentTransform(), SpawnParameters);

					ammo1 -= 1;
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), ammo1));
				}
				bReadyToFire = false;
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, projectileFireRate, false);
			}
		}
		break;
	case ECannonType::Trace:
		if(ammo2 > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Trace")));
			
			FHitResult HitResult;
			auto Start = SpawnPoint->GetComponentLocation();
			auto End = Start + SpawnPoint->GetForwardVector() * 2000;
			FCollisionObjectQueryParams ObjectQueryParams;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_Vehicle);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_Destructible);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetInstigator());
			if(GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams, Params))
			{
				DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Purple, false, 0.1, 0,5);
				if(HitResult.Actor.IsValid())
					HitResult.Actor->Destroy();
			}
			else
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 0.1, 0,5);
			}
			ammo2 -= 1;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), ammo2));

			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, traceFireRate, false);
		}
		break;
	case ECannonType::Bullets:
		{
			if(ammo3 > 0)
			{
				if(ProjectileType)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Bullet")));
					
					FActorSpawnParameters SpawnParameters;
					SpawnParameters.Instigator = GetInstigator();
					SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					GetWorld()->SpawnActor<AProjectile>(ProjectileType, SpawnPoint->GetComponentTransform(), SpawnParameters);

					ammo3 -= 1;
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), ammo3));
				}
				bReadyToFire = false;
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, bulletsFireRate, false);
			}
		}
		break;
	}

}

void ACannon::FireSpecial(int& ammo1, int& ammo2, int& ammo3)
{
	if(!bReadyToFire)
		return;
	switch (Type)
	{
	case ECannonType::Projectile:
		if(ammo1 > 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileSpecial")));
			ammo1 -= 3;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), ammo1));
			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, projectileFireRate*3, false);
		}
		break;
	case ECannonType::Trace:
		if(ammo2 > 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceSpecial")));
			ammo2 -= 3;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), ammo2));
			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, traceFireRate*3, false);
		}
		break;
	case ECannonType::Bullets:
		{
			if(ammo3 > 2)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletSpecial")));
				ammo3 -= 3;
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), ammo3));
				bReadyToFire = false;
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, bulletsFireRate*3, false);
			}
		}
		break;
	}

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


