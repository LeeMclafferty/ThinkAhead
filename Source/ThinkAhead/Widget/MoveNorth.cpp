// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveNorth.h"
#include "Kismet/Gameplaystatics.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"

void UMoveNorth::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMoveNorth::Move()
{
	Super::Move();

	if (!PlayerPawn || !PlayerCube)
		return;

	PlayerPawn->GetPlayerCube()->LookNorth();

	PlayerPawn->GetPlayerCube()->CubeSpeed = Speed;
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);

}
