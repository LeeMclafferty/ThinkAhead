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

	void ToggleOrtho();
	void ToggleMusic();
	void ToggleSounds();

	UPROPERTY(BlueprintReadWrite)
	bool bShouldPlayTransition;

	class USoundManager* GetSoundManager() { return SoundManager; }

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Initialization|LevelDetails")
	FName LevelName;

private:
	void LoadGame();

	UPROPERTY(VisibleAnywhere)
	class USoundManager* SoundManager;
};
