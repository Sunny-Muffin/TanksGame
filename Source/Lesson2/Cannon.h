// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Cannon.generated.h"


UENUM()
enum class ECannonType
{
	Projectile UMETA(DisplayName = "Projectile"),
	Trace UMETA(DisplayName = "Trace") ,
	Bullets UMETA(DisplayName = "Bullets")
};


UCLASS()
class LESSON2_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* EmptyRoot;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPoint;
	

	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	ECannonType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	float projectileFireRate = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	int projectileAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	float traceFireRate = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	int traceAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	float bulletsFireRate = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	int bulletsAmmo = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	TSubclassOf<AProjectile> ProjectileType;
	
	void Fire();
	void FireSpecial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool bReadyToFire = true;
	FTimerHandle ReloadHandle;
	void OnReload();
	void AddBulletsProj(int bullets);
	void AddBulletsTrace(int bullets);
	void AddBulletsGun(int bullets);
};



