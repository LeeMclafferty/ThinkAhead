// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/StopCube.h"

#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/WorldActor/GridTile.h"

AStopCube::AStopCube()
{

}

void AStopCube::PerformAction()
{

	if (!PlayerCube)
		return;

	PlayerCube->SetCubeState(ECubeState::ECS_Idle);
	
	if (!GetPlayersCurrentTile())
		return;

	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
	PlayerCube->SetActorLocation(TileCenter);
}
