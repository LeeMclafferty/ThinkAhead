// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveSouth.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"

void UMoveSouth::NativeConstruct()
{

}

void UMoveSouth::Move()
{
	Super::Move();

	if (!PlayerPawn)
		return;

	PlayerPawn->GetPlayerCube()->CubeSpeed = -20;
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);
}
