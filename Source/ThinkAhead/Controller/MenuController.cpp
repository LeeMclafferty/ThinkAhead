// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Controller/MenuController.h"
#include "Blueprint/UserWidget.h"

#include "ThinkAhead/Widget/Menu/MainMenu.h"
#include "ThinkAhead/Widget/Menu/LevelSelect.h"

AMenuController::AMenuController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void AMenuController::BeginPlay()
{	
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	CreateMainMenu();
}

