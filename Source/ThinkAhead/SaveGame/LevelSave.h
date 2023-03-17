// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY()
	bool bHasWonLevel;
	
};
