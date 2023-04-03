// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/Controller/MenuController.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"

void UOptionsMenu::NativeConstruct()
{

}

void UOptionsMenu::GoBack()
{
	auto Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller)
		return;

	Controller->CreatePreviousWidget();
}

void UOptionsMenu::ToggleOrthoCamera()
{
	auto Gamemode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!Gamemode)
		return;

	if (auto PlayerPawn = Cast<ACameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerPawn->ChangePerspctive();
		PlayerPawn->SwapZoomOutLimit();
		Gamemode->ToggleOrtho();
	}
	else 
	{
		Gamemode->ToggleOrtho();
	}

}
