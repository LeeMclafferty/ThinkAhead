// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Controller/CubeController.h"

#include "ThinkAhead/Widget/PlayerHud.h"

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

}

void ACubeController::CreatePlayerHud()
{
	if (!PlayerHudClass)
		return;

	PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	PlayerHud->AddToViewport();
}
