// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CheckBox.h"

#include "ThinkAhead/Controller/MenuController.h"
#include "ThinkAhead/Pawn/CameraPawn.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "ThinkAhead/GameInstance/ThinkAheadGameInstance.h"
#include "ThinkAhead/ActorComponet/SoundManager.h"

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

void UOptionsMenu::ToggleMusic()
{
	auto Gamemode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!Gamemode || !GameInst)
		return;

	Gamemode->ToggleMusic();
	bool bTurnMusicOn = GameInst->IsMusicOn();

	if (!bTurnMusicOn)
	{
		Gamemode->GetSoundManager()->StopMusic();
	}
	else
	{
		Gamemode->GetSoundManager()->PlayMusic();
	}

	SaveChanges();
}

void UOptionsMenu::ToggleSounds()
{
	auto Gamemode = Cast<AThinkAheadGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GameInst = Cast<UThinkAheadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!Gamemode || !GameInst)
		return;

	Gamemode->ToggleSounds();
	bool bTurnSoundOn = GameInst->IsSoundOn();

	if (!bTurnSoundOn)
	{
		Gamemode->GetSoundManager()->StopAmbientSounds();
	}
	else
	{
		Gamemode->GetSoundManager()->PlayAmbientSounds();
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
	MusicCheckBox->SetCheckedState(Gameinst->IsMusicOn() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	SoundCheckBox->SetCheckedState(Gameinst->IsSoundOn() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}
