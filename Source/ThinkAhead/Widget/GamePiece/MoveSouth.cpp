// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/GamePiece/MoveSouth.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveSouth::NativeConstruct()
{

}

void UMoveSouth::Move()
{
	Super::Move();

	if (!PlayerPawn || !PlayerCube)
		return;

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->LookSouth();

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed * -1);
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);
}
