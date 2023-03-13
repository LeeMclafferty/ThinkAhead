// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetCollisionProfileName(FName("Obstacle"));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

AGridTile* AObstacle::GetPlayersCurrentTile()
{
	return PlayerCube->GetCurrentTile();
}

void AObstacle::PerformAction()
{
	if (ACameraPawn* PP = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn = PP;
		PlayerCube = PlayerPawn->GetPlayerCube();
	}

	if (!PlayerCube)
		return;

	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
	PlayerCube->SetActorLocation(TileCenter);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

