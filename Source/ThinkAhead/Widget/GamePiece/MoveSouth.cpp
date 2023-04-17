// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/GamePiece/MoveSouth.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/ActorComponet/SimpleMovement.h"

void UMoveSouth::NativeConstruct()
{

}

void UMoveSouth::Move()
{
	Super::Move();

	if (!PlayerController || !PlayerCube)
		return;

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->LookSouth();

	PlayerController->GetControlledCube()->GetSimpleMovementComp()->SetMoveSpeed(Speed * -1);
	PlayerController->GetControlledCube()->SetCubeState(ECubeState::ECS_MovingNorthSouth);
}
