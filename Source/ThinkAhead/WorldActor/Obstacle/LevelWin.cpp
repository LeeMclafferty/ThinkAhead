// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/WorldActor/Obstacle/LevelWin.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"

ALevelWin::ALevelWin()
{
	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameMode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ALevelWin::PerformAction()
{
	Super::PerformAction();

	if (!PlayerController || !GameMode)
		return;

	PlayerCube->SetCubeState(ECubeState::ECS_Idle);

	if (!GetPlayersCurrentTile() || GameMode->HasWonLevel())
		return;

	GameMode->WinLevel();
	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
	PlayerCube->SetActorLocation(TileCenter);

	//Play animations / VFX here.

	PlayerController->CreateWinScreen();
}
