// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/GamePiece/MoveWest.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveWest::NativeConstruct()
{

}

void UMoveWest::Move()
{
	Super::Move();

	if (!PlayerController || !PlayerCube)
		return;

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->LookWest();

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed);
	PlayerController->GetControlledCube()->SetCubeState(ECubeState::ECS_MoveingEastWest);
}