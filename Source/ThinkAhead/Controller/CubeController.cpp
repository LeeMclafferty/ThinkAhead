// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/CubeController.h"

#include "ThinkAhead/Widget/Screen/PlayerHud.h"
#include "ThinkAhead/Widget/Move/ExecuteMoves.h"
#include "ThinkAhead/WorldActor/Controlled/ControlledCube.h"
#include "ThinkAhead/Widget/Screen/LoseScreen.h"
#include "ThinkAhead/Widget/Screen/WinScreen.h"

ACubeController::ACubeController()
	:PlayerHud(nullptr)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultClickTraceChannel = ECollisionChannel::ECC_EngineTraceChannel2;
}

void ACubeController::BeginPlay()
{
	Super::BeginPlay();
	
	CreatePlayerHud();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

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

void ACubeController::CreateLoseScreen()
{
	if (!LoseScreenClass)
		return;

	ClearViewPort();

	LoseScreen = CreateWidget<ULoseScreen>(this, LoseScreenClass);
	LoseScreen->AddToViewport();
}

void ACubeController::CreateWinScreen()
{
	if (!WinScreenClass)
		return;

	ClearViewPort();

	WinScreen = CreateWidget<UWinScreen>(this, WinScreenClass);
	WinScreen->AddToViewport();
}

void ACubeController::CreatePlayerHud()
{
	if (!PlayerHudClass)
		return;

	ClearViewPort();

	PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	PlayerHud->AddToViewport();
}

void ACubeController::ClearViewPort()
{
	if (PlayerHud)
		PlayerHud->RemoveFromParent();
	else if (LoseScreen)
		LoseScreen->RemoveFromParent();
	else if (WinScreen)
		WinScreen->RemoveFromParent();
}
