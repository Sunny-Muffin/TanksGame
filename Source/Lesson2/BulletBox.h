// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BulletBox.generated.h"

UENUM()
enum class ECannonType2
{
	Projectile2 UMETA(DisplayName = "Projectile"),
	Trace2 UMETA(DisplayName = "Trace") ,
	Bullets2 UMETA(DisplayName = "Bullets")
};

UCLASS()
class LESSON2_API ABulletBox : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Collision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	ECannonType2 Type2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
	int BulletsAmmount = 30;
	// Sets default values for this actor's properties
	ABulletBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
