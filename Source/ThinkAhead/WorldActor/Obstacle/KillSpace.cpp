// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/WorldActor/Obstacle/KillSpace.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"

AKillSpace::AKillSpace()
{
	
}

void AKillSpace::PerformAction()
{
	Super::PerformAction();

	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!PlayerController)
		return;
	
	PlayerCube->SetCubeState(ECubeState::ECS_Idle);

 	if (!GetPlayersCurrentTile())
 		return;

	PlayerCube->SetDeathMesh(DeathMesh);
	PlayerCube->SetDeathVFX(DeathVFX);
	PlayerCube->SetDeathSound(DeathSound);
	
	PlayerCube->OnDeath();

}
