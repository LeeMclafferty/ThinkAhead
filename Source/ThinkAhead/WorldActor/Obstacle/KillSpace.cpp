// Fill out your copyright notice in the Description page of Project Settings.


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

	PlayerCube->OnDeath();
	Destroy();
}
