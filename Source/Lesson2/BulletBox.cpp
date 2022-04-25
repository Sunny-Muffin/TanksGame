// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBox.h"

#include "Cannon.h"
#include "TankPawn.h"

// Sets default values
ABulletBox::ABulletBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABulletBox::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABulletBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<ATankPawn>(Other);
	if (Tank)
	{
		switch (Type2)
		{
		case ECannonType2::Projectile2:
			{
				Tank->AddBulletsProj(BulletsAmmount);
			}
			break;
		case ECannonType2::Trace2:
			{
				Tank->AddBulletsTrace(BulletsAmmount);
			}
			break;
		case ECannonType2::Bullets2:
			{
				Tank->AddBulletsGun(BulletsAmmount);
			}
			break;
		}
		Destroy();
	}
	


}

