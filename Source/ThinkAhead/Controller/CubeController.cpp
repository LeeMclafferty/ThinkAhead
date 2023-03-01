// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/CubeController.h"

#include "ThinkAhead/Widget/PlayerHud.h"
#include "ThinkAhead/Widget/ExecuteMoves.h"
#include "ThinkAhead/WorldActor/ControlledCube.h"

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

void ACubeController::CreatePlayerHud()
{
	if (!PlayerHudClass)
		return;

	PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	PlayerHud->AddToViewport();
}
