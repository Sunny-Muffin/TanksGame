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

void ACannon::Fire()
{
	if(!bReadyToFire)
		return;
	
	switch (Type)
	{
	case ECannonType::Projectile:
		{
			if(projectileAmmo > 0)
			{
				if(ProjectileType)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Projectile")));
					
					FActorSpawnParameters SpawnParameters;
					SpawnParameters.Instigator = GetInstigator();
					SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					GetWorld()->SpawnActor<AProjectile>(ProjectileType, SpawnPoint->GetComponentTransform(), SpawnParameters);

					projectileAmmo -= 1;
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), projectileAmmo));
				}
				bReadyToFire = false;
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, projectileFireRate, false);
			}
		}
		break;
	case ECannonType::Trace:
		if(traceAmmo > 0)
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
			traceAmmo -= 1;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));

			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, traceFireRate, false);
		}
		break;
	case ECannonType::Bullets:
		{
			if(bulletsAmmo > 0)
			{
				if(ProjectileType)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Bullet")));
					
					FActorSpawnParameters SpawnParameters;
					SpawnParameters.Instigator = GetInstigator();
					SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					GetWorld()->SpawnActor<AProjectile>(ProjectileType, SpawnPoint->GetComponentTransform(), SpawnParameters);

					bulletsAmmo -= 1;
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), bulletsAmmo));
				}
				bReadyToFire = false;
				GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, bulletsFireRate, false);
			}
		}
		break;
	}

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
			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, projectileFireRate*3, false);
		}
		break;
	case ECannonType::Trace:
		if(traceAmmo > 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceSpecial")));
			traceAmmo -= 3;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));
			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ACannon::OnReload, traceFireRate*3, false);
		}
		break;
	case ECannonType::Bullets:
		{
			if(bulletsAmmo > 2)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletSpecial")));
				bulletsAmmo -= 3;
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), bulletsAmmo));
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

void ACannon::AddBulletsProj(int bullets)
{
	projectileAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ProjectileAmmo left = %d"), projectileAmmo));
}

void ACannon::AddBulletsTrace(int bullets)
{
	traceAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TraceAmmo left = %d"), traceAmmo));
}

void ACannon::AddBulletsGun(int bullets)
{
	bulletsAmmo += bullets;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("BulletAmmo left = %d"), bulletsAmmo));
}

