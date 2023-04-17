// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


#include "Thinkahead/GameInstance/ThinkAheadGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/SaveGame/LevelSave.h"

UThinkAheadGameInstance::UThinkAheadGameInstance()
	:bIsOrtho(false), bIsMusicOn(true), bIsSoundsOn(true)
{
	UnlockLevel(FName("Level1"));
}

void UThinkAheadGameInstance::SaveGame()
{
	ULevelSave* LevelSave;
	if (UGameplayStatics::DoesSaveGameExist("Default", 0))
	{
		LevelSave = Cast<ULevelSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));
	}
	else
	{
		LevelSave = Cast<ULevelSave>(UGameplayStatics::CreateSaveGameObject(ULevelSave::StaticClass()));
	}

	LevelSave->SaveUnlockedLevels(UnlockedLevels);
	LevelSave->SaveSettings(bIsOrtho);
	UGameplayStatics::SaveGameToSlot(LevelSave, "Default", 0);

}

void UThinkAheadGameInstance::LoadGame()
{
	ULevelSave* LevelSave = Cast<ULevelSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));

	if (LevelSave)
	{
		UnlockedLevels = LevelSave->GetUnlockedLevels();
		bIsOrtho = LevelSave->IsOrtho();
	}
}

bool UThinkAheadGameInstance::IsLevelUnlocked(FName LevelName)
{
	return UnlockedLevels.Contains(LevelName);
}

void UThinkAheadGameInstance::UnlockLevel(FName LevelName)
{
	if (UnlockedLevels.Contains(LevelName))
		return;

	UnlockedLevels.Add(LevelName);
}
