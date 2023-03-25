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
	UThinkAheadGameInstance();

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();

	bool IsLevelUnlocked(FName LevelName);
	void UnlockLevel(FName LevelName);
	
private:

	UPROPERTY(EditDefaultsOnly, SaveGame, Category="Levels")
	TArray<FName> UnlockedLevels;
};
