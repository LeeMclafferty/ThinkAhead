// Fill out your copyright notice in the Description page of Project Settings.


#include "Thinkahead/GameInstance/ThinkAheadGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/SaveGame/LevelSave.h"

void UThinkAheadGameInstance::SaveGame()
{

	ULevelSave* LevelSave;

	if (!UGameplayStatics::DoesSaveGameExist("Default", 0))
	{
		LevelSave = Cast<ULevelSave>(UGameplayStatics::CreateSaveGameObject(ULevelSave::StaticClass()));
	}

	UGameplayStatics::SaveGameToSlot(LevelSave, "Default", 0);

}

void UThinkAheadGameInstance::LoadGame()
{
	ULevelSave* LevelSave = Cast<ULevelSave>(UGameplayStatics::CreateSaveGameObject(ULevelSave::StaticClass()));
	LevelSave = Cast<ULevelSave>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));

	if (LevelSave)
	{
		bHasWonLevel = LevelSave->bHasWonLevel;
	}
}

void UThinkAheadGameInstance::AddLevel(class AThinkAheadGameModeBase* LevelGamemode)
{

}

void UThinkAheadGameInstance::LevelName()
{

}

