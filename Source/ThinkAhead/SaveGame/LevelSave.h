// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/WorldActor/Grid/GridTile.h"
#include "GameFramework/SaveGame.h"
#include "LevelSave.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ULevelSave : public USaveGame
{
	GENERATED_BODY()

public:

	ULevelSave();

	void SaveUnlockedLevels(TArray<FName> Levels);
	TArray<FName> GetUnlockedLevels() { return UnlockedLevels; }
	void SaveSettings(bool bIsOrthoSet);
	bool IsOrtho() { return bIsOrtho; }

protected:
	UPROPERTY()
	TArray<FName> UnlockedLevels;

	UPROPERTY()
	bool bIsOrtho;
	
};
