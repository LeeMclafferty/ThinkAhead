// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/Widget/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CheckBox.h"

#include "ThinkAhead/Controller/MenuController.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"

void UOptionsMenu::NativeConstruct()
{
	SetCheckBoxes();
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
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("UOPtionsMenu::ToggleOrthoCamera")));
		Gamemode->ToggleOrtho();
		PlayerPawn->ChangePerspctive();
		PlayerPawn->SwapZoomOutLimit();
	}
	else 
	{
		Gamemode->ToggleOrtho();
	}

	SaveChanges();
}

void UOptionsMenu::SaveChanges()
{
	auto Gameinst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!Gameinst)
		return;

	Gameinst->SaveGame();
}

void UOptionsMenu::SetCheckBoxes()
{
	auto Gameinst= Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!Gameinst)
		return;

	OrthoCheckBox->SetCheckedState(Gameinst->IsOrtho() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}
