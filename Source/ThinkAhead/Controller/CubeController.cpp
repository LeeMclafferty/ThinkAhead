// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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

void ACubeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("OpenMenu", IE_Pressed, this, &ACubeController ::OpenGameSettingsMenu);
	}
}

void ACubeController::OpenGameSettingsMenu()
{
	CreateGameSettingsMenu();
}

