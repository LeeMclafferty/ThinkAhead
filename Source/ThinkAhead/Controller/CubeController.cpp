// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/CubeController.h"

#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "ThinkAhead/Widget/Move/ExecuteMoves.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Widget/Screen/LoseScreen.h"
#include "ThinkAhead/Widget/Screen/WinScreen.h"

ACubeController::ACubeController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultClickTraceChannel = ECollisionChannel::ECC_EngineTraceChannel2;
}

void ACubeController::BeginPlay()
{
	Super::BeginPlay();
	
	CreatePlayerHud();

	if (PlayerHud)
	{
		ExecuteButton = PlayerHud->GetExecuteButton();
	}

	if(ControlledCube)
		ExecuteButton->OnExecute.AddDynamic(ControlledCube, &AControlledCube::StartGame);

}

void ACubeController::SetControlledCube(AControlledCube* NewCube)
{
	ControlledCube = NewCube;
}
