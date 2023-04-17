// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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
