// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "ThinkAhead/Widget/Screen/WinScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

#include "ThinkAhead/Gamemode/LevelGamemode.h"

void UWinScreen::NativeConstruct()
{
	UnlockNextLevel();
}

void UWinScreen::PlayWinSound()
{
	if (!WinSound)
		return;

	WinAudioComp = UGameplayStatics::SpawnSound2D(GetWorld(), (USoundBase*)WinSound);
}

void UWinScreen::StopWinSound()
{
	if (WinAudioComp->IsPlaying())
		WinAudioComp->Stop();
}

void UWinScreen::UnlockNextLevel()
{
	auto Gamemode = Cast<ALevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!Gamemode)
		return;

	Gamemode->UnlockLevel();
}
