// Fill out your copyright notice in the Description page of Project Settings.


#include "ThinkAhead/SaveGame/LevelSave.h"

ULevelSave::ULevelSave()
{

}

void ULevelSave::SaveUnlockedLevels(TArray<FName> Levels)
{
	UnlockedLevels = Levels;
}

