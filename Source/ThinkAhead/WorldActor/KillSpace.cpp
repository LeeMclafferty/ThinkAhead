// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/KillSpace.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/WorldActor/GridTile.h"

AKillSpace::AKillSpace()
{
	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AKillSpace::PerformAction()
{
	Super::PerformAction();

	if (!PlayerController)
		return;
	
	PlayerCube->SetCubeState(ECubeState::ECS_Idle);

	if (!GetPlayersCurrentTile())
		return;

	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
  	PlayerCube->SetActorLocation(TileCenter);

	//Play animations / VFX here.

	PlayerController->CreateLoseScreen();
}
