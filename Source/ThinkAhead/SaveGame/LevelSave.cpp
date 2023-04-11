// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/SaveGame/LevelSave.h"
#include "Kismet/GameplayStatics.h"

#include "ThinkAhead/ThinkAheadGameModeBase.h"

ULevelSave::ULevelSave()
{

}

void ULevelSave::SaveUnlockedLevels(TArray<FName> Levels)
{
	UnlockedLevels = Levels;
}

void ULevelSave::SaveSettings(bool bIsOrthoSet)
{
	bIsOrtho = bIsOrthoSet;
}

