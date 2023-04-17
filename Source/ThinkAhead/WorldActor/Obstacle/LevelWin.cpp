// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/WorldActor/Obstacle/LevelWin.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/CubeController.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

ALevelWin::ALevelWin()
{

}

void ALevelWin::PerformAction()
{
	Super::PerformAction();

	PlayerController = Cast<ACubeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameMode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!PlayerController || !GameMode)
		return;

	PlayerCube->SetCubeState(ECubeState::ECS_Idle);

	if (!GetPlayersCurrentTile())
		return;

	FVector TileCenter = GetPlayersCurrentTile()->GetTileCenter();
	PlayerCube->SetActorLocation(TileCenter);

	//Play animations / VFX here.

	PlayerController->CreateWinScreen();
}
