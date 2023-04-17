// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.


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

void ULevelSave::SaveSettings(bool bIsOrthoSet, bool bSoundEnabled, bool bMusicEnabled)
{
	bIsOrtho = bIsOrthoSet;
	bHasSound = bSoundEnabled;
	bHasMusic = bMusicEnabled;
}

