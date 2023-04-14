// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/Obstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ThinkAhead/ActorComponet/DetectionComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetCollisionProfileName(FName("Obstacle"));

	DetectionComponent = CreateDefaultSubobject<UDetectionComponent>(TEXT("DetectionComponent"));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	SetStartingTile();
}

AGridTile* AObstacle::GetPlayersCurrentTile()
{
	return PlayerCube->GetDetectionComponent()->GetCurrentTile();
}

void AObstacle::SetStartingTile()
{
	DetectionComponent->SetCurrentTile();

	if(DetectionComponent->GetCurrentTile())
		SetActorLocation(DetectionComponent->GetCurrentTile()->GetTileCenter());
}

void AObstacle::PerformAction()
{
	if (ACubeController* Controller = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController = Controller;
		PlayerCube = PlayerController->GetControlledCube();
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

