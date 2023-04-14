// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/GamePiece/MoveNorth.h"
#include "Kismet/Gameplaystatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveNorth::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMoveNorth::Move()
{
	Super::Move();

	if (!PlayerController || !PlayerCube)
		return;

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->LookNorth();

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed);
	PlayerController->GetControlledCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);

}
