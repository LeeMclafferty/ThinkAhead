// Fill out your copyright notice in the Description page of Project Settings.


#include "Thinkahead/GameInstance/ThinkAheadGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/SaveGame/LevelSave.h"

UThinkAheadGameInstance::UThinkAheadGameInstance()
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
	UGameplayStatics::SaveGameToSlot(LevelSave, "Default", 0);

}

void UThinkAheadGameInstance::LoadGame()
{
	ULevelSave* LevelSave = Cast<ULevelSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));

	if (LevelSave)
	{
		UnlockedLevels = LevelSave->GetUnlockedLevels();
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
