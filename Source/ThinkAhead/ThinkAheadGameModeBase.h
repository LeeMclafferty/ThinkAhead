// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThinkAheadGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API AThinkAheadGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThinkAheadGameModeBase();

	UFUNCTION(BlueprintPure)
	FName GetLevelName() { return LevelName;}
	UFUNCTION(BlueprintPure)
	FName GetNextLevelName() { return NextLevelName; }

	void ToggleOrtho();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Initialization|LevelDetails")
	FName LevelName;
	UPROPERTY(EditDefaultsOnly, Category = "Initialization|LevelDetails")
	FName NextLevelName;

private:
	void LoadGame();
};
