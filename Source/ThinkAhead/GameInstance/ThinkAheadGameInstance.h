// Copyright © 2023 Lee Mclafferty. All rights reserved. This code is the property of Lee Mclafferty and may not be used for resale, redistribution, or for the purpose of making a profit without written consent from the owner.

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

	void SetIsOrtho(bool bIsOrthEnabled) { bIsOrtho = bIsOrthEnabled; }
	bool IsOrtho() { return bIsOrtho; }

	void SetIsSoundOn(bool bIsSoundEnabled) { bIsSoundsOn = bIsSoundEnabled; }
	bool IsSoundOn() { return bIsSoundsOn; }

	void SetIsMusicOn(bool bIsMusicEnabled) { bIsMusicOn = bIsMusicEnabled; }
	bool IsMusicOn() { return bIsMusicOn; }
	
private:

	UPROPERTY(EditDefaultsOnly, SaveGame, Category="Levels")
	TArray<FName> UnlockedLevels;

	UPROPERTY(SaveGame)
	bool bIsOrtho;
	UPROPERTY(SaveGame)
	bool bIsMusicOn;
	UPROPERTY(SaveGame)
	bool bIsSoundsOn;
};
