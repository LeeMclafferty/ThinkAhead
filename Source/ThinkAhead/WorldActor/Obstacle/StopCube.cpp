// Fill out your copyright notice in the Description page of Project Settings.


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

	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Purple, FString::Printf(TEXT("Hit Detected")));
	PlayerCube->SetCubeState(ECubeState::ECS_Idle);
}
