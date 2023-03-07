// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveEast.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveEast::NativeConstruct()
{

}

void UMoveEast::Move()
{
	Super::Move();

	if (!PlayerPawn || !PlayerCube)
		return;

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->LookEast();

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed * -1);
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MoveingEastWest);
}
