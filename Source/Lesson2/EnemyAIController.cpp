// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "TankPawn.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Waypoints.Empty();
	auto TankPawn = Cast<ATankPawn>(InPawn);
	if(!TankPawn)
	{
		return;
	}

	TArray<AActor*> WaypointActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AWaypoint::StaticClass(), TankPawn->WaypointTag, WaypointActors);

	WaypointActors.Sort([](const AActor& a, const AActor& b)
	{
		auto WPA = CastChecked<AWaypoint>(&a);
		auto WPB = CastChecked<AWaypoint>(&b);
		return WPA->Order > WPB->Order;
	});

	for (auto Waypoint: WaypointActors)
	{
		Waypoints.Add(Waypoint->GetActorLocation());
	}
	NextWaypoint = 0;
}


