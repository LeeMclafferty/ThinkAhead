// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ThinkAheadGameInstance.generated.h"

UCLASS()
class THINKAHEAD_API UThinkAheadGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SaveGame();
	UFUNCTION()
	void LoadGame();

	void AddLevel(class AThinkAheadGameModeBase* LevelGamemode);
	
private:

	TArray<AThinkAheadGameModeBase> Levels;
	
};
