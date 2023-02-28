// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveWest.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"

void UMoveWest::NativeConstruct()
{

}

void UMoveWest::Move()
{
	Super::Move();

	if (!PlayerPawn)
		return;

	PlayerPawn->GetPlayerCube()->CubeSpeed = 20;
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MoveingEastWest);
}

