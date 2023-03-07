// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveWest.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveWest::NativeConstruct()
{

}

void UMoveWest::Move()
{
	Super::Move();

	if (!PlayerPawn || !PlayerCube)
		return;

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->LookWest();

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed);
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MoveingEastWest);
}

