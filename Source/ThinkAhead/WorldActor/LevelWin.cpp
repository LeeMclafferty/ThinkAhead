// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/LevelWin.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"
#include "ThinkAhead/WorldActor/GridTile.h"

ALevelWin::ALevelWin()
{
	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ALevelWin::PerformAction()
{
	Super::PerformAction();

	if (!PlayerController)
		return;

	PlayerCube->SetCubeState(ECubeState::ECS_Idle);

	if (!GetPlayersCurrentTile())
		return;

	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
	PlayerCube->SetActorLocation(TileCenter);

	//Play animations / VFX here.

	PlayerController->CreateWinScreen();
}
