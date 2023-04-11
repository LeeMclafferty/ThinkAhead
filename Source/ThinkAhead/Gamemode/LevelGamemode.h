// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThinkAhead/ThinkAheadGameModeBase.h"
#include "LevelGamemode.generated.h"

/**
 * 
 */
UCLASS()
class THINKAHEAD_API ALevelGamemode : public AThinkAheadGameModeBase
{
	GENERATED_BODY()

public:
	ALevelGamemode();

	UFUNCTION(BlueprintPure)
	int32 GetNumMovestoMake() { return NumOfMovesToMake; }
	UFUNCTION(BlueprintPure)
	int32 GetNumMoveOptions() { return NumMoveOptions; }
	UFUNCTION(BlueprintPure)
	TArray<class UMovePiece*> GetStartingPieces() { return StaringPieces; }

	void LevelLost();

protected:
	virtual void BeginPlay() override;
	// Total Number of moves that can be executed for a level.
	UPROPERTY(EditDefaultsOnly, Category = "Initialization|Gameplay")
	int32 NumOfMovesToMake;
	// All of the possible moves to select from. 
	UPROPERTY(EditDefaultsOnly, Category = "Initialization|Gameplay")
	int32 NumMoveOptions;

	UPROPERTY(EditDefaultsOnly, Category = "Initialization|TSubclassOf")
	TArray<TSubclassOf<class UMovePiece>> StartingPieceClasses;

	UPROPERTY(VisibleAnywhere)
	TArray<class UMovePiece*> StaringPieces;

	void CreateStartingPieces();

private:
	void UnlockLevel();
	
};
