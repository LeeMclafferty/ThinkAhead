// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/WorldActor/Obstacle/StopCube.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ThinkAhead/Pawn/CameraPawn.h"

AStopCube::AStopCube()
{

}

void AStopCube::PerformAction()
{
	Super::PerformAction();

	if (!PlayerCube)
		return;

	PlayerCube->SetCubeState(ECubeState::ECS_Idle);
}
