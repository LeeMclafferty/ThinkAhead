// Fill out your copyright notice in the Description page of Project Settings.


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

void AMenuController::CreateMainMenu()
{
	SetupWidget(MainMenuClass);
}

void AMenuController::CreateLevelSelect()
{
	SetupWidget(LevelSelectClass);
}

void AMenuController::CreateQuitPopup()
{
	SetupWidget(ExitPopupClass);
}

void AMenuController::CreateOptionsMenu()
{
	SetupWidget(OptionsMenuClass);
}
