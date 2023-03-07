// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/MoveNorth.h"
#include "Kismet/Gameplaystatics.h"

#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveNorth::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMoveNorth::Move()
{
	Super::Move();

	if (!PlayerPawn || !PlayerCube)
		return;

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->LookNorth();

	PlayerPawn->GetPlayerCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed);
	PlayerPawn->GetPlayerCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);

}
