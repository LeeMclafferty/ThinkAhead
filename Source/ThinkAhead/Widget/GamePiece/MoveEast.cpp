// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/GamePiece/MoveEast.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveEast::NativeConstruct()
{

}

void UMoveEast::Move()
{
	Super::Move();

	if (!PlayerController || !PlayerCube)
		return;

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->LookEast();

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed * -1);
	PlayerController->GetControlledCube()->SetCubeState(ECubeState::ECS_MoveingEastWest);
}
